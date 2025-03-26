#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdint.h>

void check_time_t_limits() {
    printf("Розмір time_t: %zu байт\n", sizeof(time_t));


    time_t max_time = INT_MAX;  
    
    #if defined(__LP64__) || defined(_LP64)
        max_time = LONG_MAX;  
    #endif

    printf("Максимальне значення time_t: %lld\n", (long long)max_time);

    time_t current_max = max_time;
    struct tm *timeinfo = localtime(&current_max);
    
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    printf("Дата закінчення часу: %s\n", buffer);

    #ifdef __x86_64__
        printf("Архітектура: 64-біт (x86_64)\n");
    #elif defined(__i386__)
        printf("Архітектура: 32-біт (x86)\n");
    #else
        printf("Невідома архітектура\n");
    #endif
}

int main() {
    check_time_t_limits();
    return 0;
}
