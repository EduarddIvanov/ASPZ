#include <stdio.h>
#include <stdlib.h>

void function_frame_demo() {
    int a = 5;
    int b = 10;
    void *return_address;
    
    #if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
    __asm__ volatile (
        #ifdef __x86_64__
        "movq 8(%%rbp), %0"
        #else
        "movl 4(%%ebp), %0"
        #endif
        : "=r" (return_address)
    );
    #else
    return_address = NULL;
    #endif
    
    printf("Аналіз кадру стеку:\n");
    printf("Адреса локальної змінної a: %p\n", (void*)&a);
    printf("Адреса локальної змінної b: %p\n", (void*)&b);
    printf("Адреса повернення (зберігається на стеку): %p\n", return_address);
    
}

int main() {
    printf("== Дослідження взаємодії стеку і лічильника команд (IP) ==\n\n");
    function_frame_demo();
    
    return 0;
}
