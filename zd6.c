#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    int i;
    
    for (i = 1; i <= 5; i++) {
        pid = fork();
        
        if (pid == 0) {
            printf("Дочірній процес %d\n", i);
            exit(0);
        }
    }
    
    for (i = 0; i < 5; i++) {
        wait(NULL);
    }
    
    return 0;
}
