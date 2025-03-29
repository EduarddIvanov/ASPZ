#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>

#define GB (1024ULL * 1024 * 1024)
#define TEST_ITERATIONS 10

void large_memory_allocation_test() {
    printf("\nЗавдання 6: Тестування malloc при високому навантаженні\n");
    
    size_t sizes[] = {
        100 * MB,     // 100 МБ
        500 * MB,     // 500 МБ
        1 * GB,       // 1 ГБ
        2 * GB,       // 2 ГБ
        4 * GB        // 4 ГБ
    };
    
    for (int i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
        clock_t start, end;
        double cpu_time_used;
        
        printf("\nВиділення %zu байтів\n", sizes[i]);
        
        start = clock();
        void *ptr = malloc(sizes[i]);
        end = clock();
        
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        
        if (ptr == NULL) {
            printf("Помилка виділення пам'яті\n");
            perror("malloc");
            continue;
        }
        memset(ptr, 0, sizes[i]);
        
        printf("Успішно виділено. Час виділення: %f сек\n", cpu_time_used);
        
        free(ptr);
    }
}

void memory_stress_test() {
    printf("\nТестування послідовного виділення пам'яті\n");
    
    void *ptrs[TEST_ITERATIONS];
    size_t sizes[TEST_ITERATIONS];
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        sizes[i] = (i + 1) * 10 * MB;  // Зростаючі розміри
        ptrs[i] = malloc(sizes[i]);
        
        if (ptrs[i] == NULL) {
            printf("Помилка виділення пам'яті на ітерації %d\n", i);
            break;
        }
        
        memset(ptrs[i], rand(), sizes[i]);
    }
    
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        if (ptrs[i] != NULL) {
            free(ptrs[i]);
        }
    }
}

void check_memory_limits() {
    struct rlimit rlim;
    
    printf("\nПеревірка системних обмежень пам'яті\n");
    
    if (getrlimit(RLIMIT_AS, &rlim) == 0) {
        printf("Максимальний розмір віртуальної пам'яті:\n");
        printf("М'яке обмеження: %lld байтів\n", (long long)rlim.rlim_soft);
        printf("Жорстке обмеження: %lld байтів\n", (long long)rlim.rlim_hard);
    }

    if (getrlimit(RLIMIT_DATA, &rlim) == 0) {
        printf("\nОбмеження на дані процесу:\n");
        printf("М'яке обмеження: %lld байтів\n", (long long)rlim.rlim_soft);
        printf("Жорстке обмеження: %lld байтів\n", (long long)rlim.rlim_hard);
    }
}

int main() {
    srand(time(NULL));
    
    large_memory_allocation_test();
    memory_stress_test();
    check_memory_limits();
    
    return 0;
}
