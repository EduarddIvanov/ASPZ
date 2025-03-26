#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void recursive_function(int depth) {
    char large_local_array[1024];
    large_local_array[0] = depth;
    
    if (depth > 0) {
        recursive_function(depth - 1);
    }
}

void set_stack_limit(int size_kb) {
    struct rlimit rlim;
    rlim.rlim_cur = size_kb * 1024;
    rlim.rlim_max = size_kb * 1024;

    if (setrlimit(RLIMIT_STACK, &rlim) == -1) {
        perror("Помилка встановлення обмеження стеку");
    }
}

int main() {
    set_stack_limit(64);
    
    printf("Демонстрація обмеження стеку\n");
    
    recursive_function(1000);
    
    return 0;
}
