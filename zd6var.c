#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <linux/ptrace.h>

#define MAX_STACK_FRAMES 50
#define MAX_MEMORY_DUMP 1024
#define LOG_FILE "/var/log/enhanced_crash.log"

typedef struct {
    pid_t pid;
    int signal;
    struct user_regs_struct regs;
    char stack_dump[MAX_MEMORY_DUMP];
    char heap_dump[MAX_MEMORY_DUMP];
    time_t crash_time;
} crash_info_t;

void write_crash_log(crash_info_t *info) {
    FILE *log = fopen(LOG_FILE, "a");
    if (!log) return;
    
    fprintf(log, "\n=== ENHANCED CRASH LOG ===\n");
    fprintf(log, "Time: %s", ctime(&info->crash_time));
    fprintf(log, "PID: %d\n", info->pid);
    fprintf(log, "Signal: %d (%s)\n", info->signal, strsignal(info->signal));
    
    fprintf(log, "\nRegisters:\n");
    fprintf(log, "RIP: 0x%llx\n", info->regs.rip);
    fprintf(log, "RSP: 0x%llx\n", info->regs.rsp);
    fprintf(log, "RBP: 0x%llx\n", info->regs.rbp);
    fprintf(log, "RAX: 0x%llx\n", info->regs.rax);
    fprintf(log, "RBX: 0x%llx\n", info->regs.rbx);
    fprintf(log, "RCX: 0x%llx\n", info->regs.rcx);
    fprintf(log, "RDX: 0x%llx\n", info->regs.rdx);
    
    fprintf(log, "\nStack dump (first 256 bytes):\n");
    for (int i = 0; i < 256 && i < MAX_MEMORY_DUMP; i += 16) {
        fprintf(log, "%04x: ", i);
        for (int j = 0; j < 16 && (i + j) < 256; j++) {
            fprintf(log, "%02x ", (unsigned char)info->stack_dump[i + j]);
        }
        fprintf(log, "\n");
    }
    
    fprintf(log, "========================\n\n");
    fclose(log);
}

int read_memory_range(pid_t pid, unsigned long addr, char *buffer, size_t size) {
    for (size_t i = 0; i < size; i += sizeof(long)) {
        errno = 0;
        long data = ptrace(PTRACE_PEEKDATA, pid, addr + i, NULL);
        if (errno != 0) return -1;
        
        size_t copy_size = (size - i < sizeof(long)) ? size - i : sizeof(long);
        memcpy(buffer + i, &data, copy_size);
    }
    return 0;
}

void collect_crash_info(pid_t pid, int signal, crash_info_t *info) {
    info->pid = pid;
    info->signal = signal;
    info->crash_time = time(NULL);
    
    if (ptrace(PTRACE_GETREGS, pid, NULL, &info->regs) == -1) {
        perror("ptrace GETREGS");
        return;
    }
    
    memset(info->stack_dump, 0, MAX_MEMORY_DUMP);
    if (read_memory_range(pid, info->regs.rsp, info->stack_dump, MAX_MEMORY_DUMP) == -1) {
        strcpy(info->stack_dump, "Failed to read stack memory");
    }
    
    memset(info->heap_dump, 0, MAX_MEMORY_DUMP);
}

void signal_handler(int sig, siginfo_t *si, void *unused) {
    pid_t child_pid = si->si_pid;
    crash_info_t crash_info;
    
    if (ptrace(PTRACE_ATTACH, child_pid, NULL, NULL) == -1) {
        perror("ptrace ATTACH");
        return;
    }
    
    int status;
    waitpid(child_pid, &status, 0);
    
    collect_crash_info(child_pid, sig, &crash_info);
    write_crash_log(&crash_info);
    
    ptrace(PTRACE_DETACH, child_pid, NULL, NULL);
}

void install_signal_handlers() {
    struct sigaction sa;
    sa.sa_sigaction = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    
    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGBUS, &sa, NULL);
    sigaction(SIGFPE, &sa, NULL);
    sigaction(SIGILL, &sa, NULL);
    sigaction(SIGABRT, &sa, NULL);
}

int monitor_process(pid_t target_pid) {
    if (ptrace(PTRACE_ATTACH, target_pid, NULL, NULL) == -1) {
        perror("ptrace ATTACH");
        return -1;
    }
    
    int status;
    while (1) {
        pid_t pid = waitpid(target_pid, &status, 0);
        if (pid == -1) {
            perror("waitpid");
            break;
        }
        
        if (WIFSTOPPED(status)) {
            int sig = WSTOPSIG(status);
            
            if (sig == SIGSEGV || sig == SIGBUS || sig == SIGFPE || 
                sig == SIGILL || sig == SIGABRT) {
                
                crash_info_t crash_info;
                collect_crash_info(target_pid, sig, &crash_info);
                write_crash_log(&crash_info);
                
                printf("Process %d crashed with signal %d. Log written to %s\n", 
                       target_pid, sig, LOG_FILE);
                
                ptrace(PTRACE_CONT, target_pid, NULL, sig);
            } else {
                ptrace(PTRACE_CONT, target_pid, NULL, sig);
            }
        } else if (WIFEXITED(status) || WIFSIGNALED(status)) {
            printf("Process %d terminated\n", target_pid);
            break;
        }
    }
    
    ptrace(PTRACE_DETACH, target_pid, NULL, NULL);
    return 0;
}

void create_test_crash() {
    printf("Creating test crash in 3 seconds...\n");
    sleep(3);
    
    int *p = NULL;
    *p = 42;
}

int main(int argc, char *argv[]) {
    if (geteuid() != 0) {
        fprintf(stderr, "This program requires root privileges\n");
        return 1;
    }
    
    if (argc < 2) {
        printf("Usage: %s <pid>|test\n", argv[0]);
        printf("  <pid>  - Monitor specific process ID\n");
        printf("  test   - Create test crash for demonstration\n");
        return 1;
    }
    
    if (strcmp(argv[1], "test") == 0) {
        pid_t child = fork();
        if (child == 0) {
            create_test_crash();
            return 0;
        } else if (child > 0) {
            printf("Monitoring test process %d\n", child);
            return monitor_process(child);
        } else {
            perror("fork");
            return 1;
        }
    }
    
    pid_t target_pid = atoi(argv[1]);
    if (target_pid <= 0) {
        fprintf(stderr, "Invalid PID: %s\n", argv[1]);
        return 1;
    }
    
    if (kill(target_pid, 0) == -1) {
        perror("Process not found");
        return 1;
    }
    
    printf("Starting enhanced crash monitor for PID %d\n", target_pid);
    printf("Logs will be written to: %s\n", LOG_FILE);
    
    return monitor_process(target_pid);
}
