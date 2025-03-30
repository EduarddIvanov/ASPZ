#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

void set_cpu_time_limit(int seconds) {
    struct rlimit rlim;
    rlim.rlim_cur = seconds;
    rlim.rlim_max = seconds;

    if (setrlimit(RLIMIT_CPU, &rlim) == -1) {
        perror("Помилка встановлення обмеження часу CPU");
    }
}

void simulate_lottery() {
    set_cpu_time_limit(5);
    
    srand(time(NULL));
    
    int lottery_main[7];
    int lottery_additional[6];

    for (int i = 0; i < 7; i++) {
        int num;
        int unique;
        do {
            unique = 1;
            num = rand() % 49 + 1;
            
            for (int j = 0; j < i; j++) {
                if (lottery_main[j] == num) {
                    unique = 0;
                    break;
                }
            }
        } while (!unique);
        
        lottery_main[i] = num;
    }
    
    for (int i = 0; i < 6; i++) {
        int num;
        int unique;
        do {
            unique = 1;
            num = rand() % 36 + 1;
            
            for (int j = 0; j < i; j++) {
                if (lottery_additional[j] == num) {
                    unique = 0;
                    break;
                }
            }
        } while (!unique);
        
        lottery_additional[i] = num;
    }
    
    printf("Основні числа (7 з 49): ");
    for (int i = 0; i < 7; i++) {
        printf("%d ", lottery_main[i]);
    }
    printf("\nДодаткові числа (6 з 36): ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", lottery_additional[i]);
    }
    printf("\n");
}

int main() {
    simulate_lottery();
    return 0;
}
