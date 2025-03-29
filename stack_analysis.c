#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MSG "У функції %20s; адреса локальної змінної = %p\n"

static void bar_is_now_closed(void) {
    int localvar = 5;
    printf(MSG, __func__, &localvar);
    printf("\nТепер блокується на pause()...\n");
    printf("PID процесу: %d\n", getpid());
    printf("Для аналізу стеку використовуйте:\n");
    printf("1. gstack %d\n", getpid());
    printf("2. або підключіться через GDB: gdb -quiet -p %d, потім виконайте bt\n", getpid());
    pause();
}

static void bar(void) {
    int localvar = 5;
    printf(MSG, __func__, &localvar);
    bar_is_now_closed();
}

static void foo(void) {
    int localvar = 5;
    printf(MSG, __func__, &localvar);
    bar();
}

int main(int argc, char **argv) {
    int localvar = 5;
    printf(MSG, __func__, &localvar);
    foo();
    
    return EXIT_SUCCESS;
}
