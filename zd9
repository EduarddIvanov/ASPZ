#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    struct timespec start, end;
    long elapsed_ms;
    int i;
    
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    for (i = 0; i < 1000000; i++) {
        volatile int x = i * i;
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    elapsed_ms = (end.tv_sec - start.tv_sec) * 1000 + 
                 (end.tv_nsec - start.tv_nsec) / 1000000;
    
    printf("Execution time: %ld milliseconds\n", elapsed_ms);
    
    return 0;
}
