#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

void recursive_function(int depth, int *array) {
    int local_array[1024];
    
    for(int i = 0; i < 1024; i++) {
        local_array[i] = depth;
    }

    if(depth > 0) {
        recursive_function(depth - 1, local_array);
    }
}

int main() {
    struct rlimit stack_limit;
    
    getrlimit(RLIMIT_STACK, &stack_limit);
    printf("Поточне обмеження стека: %ld байт\n", stack_limit.rlim_cur);

    for(int depth = 1000; depth <= 100000; depth *= 2) {
        int *test_array = malloc(sizeof(int) * 1024);
        
        printf("Спроба рекурсії з глибиною %d... ", depth);
        
        recursive_function(depth, test_array);
        
        printf("Успішно!\n");
        
        free(test_array);
    }

    return 0;
}
