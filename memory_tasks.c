#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <errno.h>

// Завдання 4.1
void task_4_1() {
    printf("Завдання 4.1: Максимальний обсяг пам'яті\n");
    
    printf("Розмір size_t: %zu байтів\n", sizeof(size_t));

    size_t max_size = -1; 
    printf("Максимальне значення size_t: %zu\n", max_size);
    void *ptr = malloc(max_size);
    if (ptr == NULL) {
        perror("Не вдалося виділити пам'ять");
    }
}

// Завдання 4.2
void task_4_2() {
    printf("\nЗавдання 4.2: Від'ємні аргументи та переповнення\n");

    int negative_size = -100;
    void *ptr1 = malloc(negative_size);
    if (ptr1 == NULL) {
        perror("Від'ємний розмір");
    }

    int xa = INT_MAX;
    int xb = 2;
    int num = xa * xb;  
    
    printf("xa = %d, xb = %d, num = %d\n", xa, xb, num);
    void *ptr2 = malloc(num);
    if (ptr2 == NULL) {
        perror("Переповнення при множенні");
    }
}

// Завдання 4.3
void task_4_3() {
    printf("\nЗавдання 4.3: malloc(0)\n");
    
    void *ptr1 = malloc(0);
    printf("malloc(0) повертає: %p\n", ptr1);
    
    if (ptr1 != NULL) {
        free(ptr1);
        printf("Можна викликати free()\n");
    }
}

// Завдання 4.4
void task_4_4() {
    printf("\nЗавдання 4.4: Помилки в циклі malloc/free\n");
    
    void *ptr = NULL;
    for (int i = 0; i < 5; i++) {
        if (!ptr)
            ptr = malloc(10);
        
        printf("Ітерація %d, ptr = %p\n", i, ptr);
        free(ptr);
        ptr = NULL;  
    }
}

// Завдання 4.5
void task_4_5() {
    printf("\nЗавдання 4.5: Помилка realloc\n");
    
    int *large_array = malloc(1000 * sizeof(int));
    if (large_array == NULL) {
        perror("Помилка initial malloc");
        return;
    }
    
    int *new_array = realloc(large_array, SIZE_MAX);
    if (new_array == NULL) {
        perror("Помилка realloc");
        free(large_array);  
    }
}

// Завдання 4.6
void task_4_6() {
    printf("\nЗавдання 4.6: Особливі випадки realloc\n");
    
    // realloc(NULL, size) еквівалентно malloc(size)
    int *ptr1 = realloc(NULL, 100 * sizeof(int));
    printf("realloc(NULL, size): %p\n", (void*)ptr1);
    
    // realloc(ptr, 0) еквівалентно free(ptr)
    int *ptr2 = malloc(50 * sizeof(int));
    ptr2 = realloc(ptr2, 0);
    printf("realloc(ptr, 0): %p\n", (void*)ptr2);
}

// Завдання 4.7
#include <reallocarray.h>

struct sbar {
    int data;
};

void task_4_7() {
    printf("\nЗавдання 4.7: reallocarray\n");
    
    struct sbar *ptr = calloc(1000, sizeof(struct sbar));
    struct sbar *newptr = reallocarray(ptr, 500, sizeof(struct sbar));
    
    if (newptr == NULL) {
        perror("Помилка reallocarray");
        free(ptr);
    }
}

int main() {
    task_4_1();
    task_4_2();
    task_4_3();
    task_4_4();
    task_4_5();
    task_4_6();
    task_4_7();
    
    return 0;
}
