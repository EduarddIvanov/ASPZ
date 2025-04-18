#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    while (1) {
        void *ptr = malloc(1);
        usleep(100000);  
        printf("Memory allocated\n");
    }

    return 0;
}
