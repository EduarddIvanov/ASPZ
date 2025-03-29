#include <stdio.h>
#include <stdlib.h>

int global_array[1000];
int global_init_array[1000] = {[0 ... 999] = 42};

void hello_world_demo() {
    printf("Hello, World!\n");
}
void local_array_demo() {
    int local_uninit_array[1000];
    int local_init_array[1000] = {[0 ... 999] = 55};
    printf("Локальний неініційований масив: %p\n", (void*)local_uninit_array);
    printf("Локальний ініційований масив: %p\n", (void*)local_init_array);
}
void segment_address_demo() {
    static int static_var = 100;            
    static int static_uninit_var;           
    int *heap_var = malloc(sizeof(int));    
    printf("\nАдреси різних сегментів:\n");
    printf("Глобальний неініційований масив (BSS): %p\n", (void*)global_array);
    printf("Глобальний ініційований масив (Data): %p\n", (void*)global_init_array);
    printf("Статична ініційована змінна (Data): %p\n", (void*)&static_var);
    printf("Статична неініційована змінна (BSS): %p\n", (void*)&static_uninit_var);
    printf("Динамічно виділена пам'ять (Heap): %p\n", (void*)heap_var);
    printf("Адреса функції (Text): %p\n", (void*)hello_world_demo);
    free(heap_var);
}

int main() {
    hello_world_demo();
    local_array_demo();
    segment_address_demo();
    return 0;
}
