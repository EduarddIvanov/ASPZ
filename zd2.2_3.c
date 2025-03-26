#include <stdio.h>
#include <stdlib.h>


// -----------
void hello_world_demo() {
    printf("Hello, World!\n");
}

// -----------
int global_array[1000];

// -----------
int global_init_array[1000] = {[0 ... 999] = 42};

// -----------
void local_array_demo() {
    int local_uninit_array[1000];

    int local_init_array[1000] = {[0 ... 999] = 55};

    printf("Локальний неініційований масив: %p\n", (void*)local_uninit_array);
    printf("Локальний ініційований масив: %p\n", (void*)local_init_array);
}

// -----------
void segment_address_demo() {
    static int static_var = 100;
    static int static_uninit_var;

    int *heap_var = malloc(sizeof(int));

    printf("\nАдреси різних сегментів:\n");
    printf("Статична ініційована змінна (Data): %p\n", (void*)&static_var);
    printf("Статична неініційована змінна (BSS): %p\n", (void*)&static_uninit_var);
    printf("Динамічно виділена пам'ять (Heap): %p\n", (void*)heap_var);

    free(heap_var);
}

// -----------
void stack_top_demo() {
    int stack_var;
    printf("Адреса змінної в стеку: %p\n", (void*)&stack_var);

    int large_local_array1[10000];
    int large_local_array2[10000];

    printf("Адреса великого локального масиву 1: %p\n", (void*)large_local_array1);
    printf("Адреса великого локального масиву 2: %p\n", (void*)large_local_array2);
}

int main() {
    hello_world_demo();
    local_array_demo();
    segment_address_demo();
    stack_top_demo();

    return 0;
}
