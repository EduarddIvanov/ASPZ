#include <stdio.h>

void stack_top_demo() {
    int stack_var;
    printf("Адреса змінної в стеку: %p\n", (void*)&stack_var);
    int large_local_array1[10000];
    int large_local_array2[10000];

    printf("Адреса великого локального масиву 1: %p\n", (void*)large_local_array1);
    printf("Адреса великого локального масиву 2: %p\n", (void*)large_local_array2);
    printf("Різниця між адресами масивів: %ld байт\n", 
           (long)((void*)large_local_array1 - (void*)large_local_array2));
}

void nested_function_level2() {
    int local_var2;
    printf("Адреса змінної на рівні 2: %p\n", (void*)&local_var2);
}

void nested_function_level1() {
    int local_var1;
    printf("Адреса змінної на рівні 1: %p\n", (void*)&local_var1);
    nested_function_level2();
}

int main() {
    printf("=== Дослідження структури стеку ===\n");
    
    stack_top_demo();
    
    printf("\n=== Дослідження стеку викликів ===\n");
    nested_function_level1();
    
    return 0;
}
