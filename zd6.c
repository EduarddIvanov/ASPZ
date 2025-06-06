#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

static int remaining_seconds = 0;
static int running = 1;

void timer_handler(int sig) {
    if (remaining_seconds > 0) {
        int hours = remaining_seconds / 3600;
        int minutes = (remaining_seconds % 3600) / 60;
        int seconds = remaining_seconds % 60;
        
        char buf[64];
        snprintf(buf, sizeof(buf), "\r%02d:%02d:%02d залишилось", hours, minutes, seconds);
        write(STDOUT_FILENO, buf, strlen(buf));
        
        remaining_seconds--;
        alarm(1);
    } else {
        char msg[] = "\rПодія настала! 00:00:00\n";
        write(STDOUT_FILENO, msg, strlen(msg));
        running = 0;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Використання: %s <години> <хвилини> <секунди>\n", argv[0]);
        return 1;
    }
    
    int hours = atoi(argv[1]);
    int minutes = atoi(argv[2]);
    int seconds = atoi(argv[3]);
    
    if (hours < 0 || minutes < 0 || seconds < 0 || minutes >= 60 || seconds >= 60) {
        printf("Неправильний формат часу\n");
        return 1;
    }
    
    remaining_seconds = hours * 3600 + minutes * 60 + seconds;
    
    if (remaining_seconds == 0) {
        printf("Подія вже настала!\n");
        return 0;
    }
    
    struct sigaction sa;
    sa.sa_handler = timer_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, NULL);
    
    printf("Зворотний відлік до події:\n");
    timer_handler(SIGALRM);
    
    while (running) {
        pause();
    }
    
    return 0;
}
