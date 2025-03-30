#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <errno.h>

void investigate_locked_memory() {
    struct rlimit rlim;


    if (getrlimit(RLIMIT_MEMLOCK, &rlim) == -1) {
        perror("Помилка отримання обмежень");
        return;
    }

    printf("Поточні обмеження locked memory:\n");
    printf("М'яке обмеження (soft limit): %ld KB\n", rlim.rlim_soft / 1024);
    printf("Жорстке обмеження (hard limit): %ld KB\n", rlim.rlim_hard / 1024);


    rlim.rlim_soft = 16 * 1024 * 1024;  // 16 MB
    rlim.rlim_hard = 32 * 1024 * 1024;  // 32 MB

    if (setrlimit(RLIMIT_MEMLOCK, &rlim) == -1) {
        perror("Помилка встановлення обмежень");
        switch(errno) {
            case EINVAL:
                printf("Некоректне обмеження\n");
                break;
            case EPERM:
                printf("Недостатньо прав для зміни обмежень\n");
                break;
        }
    } else {
        printf("Нові обмеження успішно встановлені\n");
    }
}

int main() {
    investigate_locked_memory();
    return 0;
}
