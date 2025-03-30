# ASPZ

# Дослідження виділення пам'яті в мові C

## Опис проекту
Тести та дослідження виділення пам'яті в мові C, зокрема роботи функцій `malloc()`, `realloc()`, `calloc()`, `free()`

### Основні функції
- **malloc(size_t size)** - виділяє блок пам'яті вказаного розміру
- **calloc(size_t nmemb, size_t size)** - виділяє та ініціалізує нулями блок пам'яті
- **realloc(void *ptr, size_t size)** - змінює розмір раніше виділеного блоку пам'яті
- **reallocarray(void *ptr, size_t nmemb, size_t size)** - безпечне перевиділення масивів з перевіркою переповнення
- **free(void *ptr)** - звільняє раніше виділений блок пам'яті

## Завдання

### 4.1 Максимальний обсяг пам'яті
#### Опис
Дослідження максимального обсягу пам'яті, який може бути виділений за один виклик `malloc()`.

#### Реалізація
```c
void task_4_1() {
    printf("Розмір size_t: %zu байтів\n", sizeof(size_t));
    size_t max_size = -1; 
    printf("Максимальне значення size_t: %zu\n", max_size);
    void *ptr = malloc(max_size);
    if (ptr == NULL) {
        perror("Не вдалося виділити пам'ять");
    }
}
```

#### Очікувані результати
- На 64-бітних системах: `sizeof(size_t)` = 8 байтів
- На 32-бітних системах: `sizeof(size_t)` = 4 байти
- Виклик `malloc()` з максимальним значенням зазвичай призводить до помилки

### 4.2 Обробка від'ємних аргументів та переповнення
#### Опис
Дослідження поведінки `malloc()` при передачі від'ємних значень та при переповненні цілих чисел.

#### Реалізація
```c
void task_4_2() {
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
```

#### Очікувані результати
- Від'ємний аргумент: `malloc()` інтерпретує його як велике додатне число і поверне NULL
- При переповненні: `num` буде менше очікуваного значення, що призведе до виділення недостатнього обсягу пам'яті

### 4.3 Виклик `malloc(0)`
#### Опис
Вивчення поведінки `malloc()` при виклику з нульовим розміром.

#### Реалізація
```c
void task_4_3() {
    void *ptr1 = malloc(0);
    printf("malloc(0) повертає: %p\n", ptr1);
    
    if (ptr1 != NULL) {
        free(ptr1);
        printf("Можна викликати free()\n");
    }
}
```

#### Очікувані результати
- В більшості реалізацій `malloc(0)` поверне ненульовий вказівник
- Цей вказівник безпечно передавати у `free()`

### 4.4 Помилки в циклі виділення пам'яті
#### Опис
Ідентифікація помилок при виділенні та звільненні пам'яті в циклі.

#### Проблемний код
```c
void *ptr = NULL;
while (<some-condition-is-true>) {
    if (!ptr)
        ptr = malloc(n);
    [... <використання 'ptr'> ...]
    free(ptr);
}
```

#### Правильний код
```c
void *ptr = NULL;
while (<some-condition-is-true>) {
    if (!ptr)
        ptr = malloc(n);
    [... <використання 'ptr'> ...]
    free(ptr);
    ptr = NULL; 
}
```

#### Реалізація тесту
```c
void task_4_4() {
    void *ptr = NULL;
    for (int i = 0; i < 5; i++) {
        if (!ptr)
            ptr = malloc(10);
        
        printf("Ітерація %d, ptr = %p\n", i, ptr);
        free(ptr);
        ptr = NULL; 
    }
}
```

#### Очікувані результати
- Без занулення вказівника: повторне використання звільненої пам'яті
- З зануленням: безпечне повторне виділення на наступній ітерації

### 4.5 Обробка помилок `realloc()`
#### Опис
Тестування сценаріїв невдалого перевиділення пам'яті.

#### Реалізація
```c
void task_4_5() {
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
```

#### Очікувані результати
- `realloc()` з надто великим розміром поверне NULL
- Оригінальний вказівник `large_array` залишиться валідним
- Програма повинна звільнити оригінальний блок пам'яті

### 4.6 Особливі випадки `realloc()`
#### Опис
Дослідження поведінки `realloc()` з `NULL` та нульовим розміром.

#### Реалізація
```c
void task_4_6() {
    int *ptr1 = realloc(NULL, 100 * sizeof(int));
    printf("realloc(NULL, size): %p\n", (void*)ptr1);
    int *ptr2 = malloc(50 * sizeof(int));
    ptr2 = realloc(ptr2, 0);
    printf("realloc(ptr, 0): %p\n", (void*)ptr2);
}
```

#### Очікувані результати
- `realloc(NULL, size)` поверне ненульовий вказівник на нову пам'ять
- `realloc(ptr, 0)` поверне NULL і звільнить пам'ять, на яку вказує `ptr`

### 4.7 Використання `reallocarray()`
#### Опис
Демонстрація безпечного перевиділення масивів за допомогою `reallocarray()`.

#### Початковий код
```c
struct sbar *ptr, *newptr;
ptr = calloc(1000, sizeof(struct sbar));
newptr = realloc(ptr, 500*sizeof(struct sbar));
```

#### Покращений код з `reallocarray()`
```c
struct sbar *ptr, *newptr;
ptr = calloc(1000, sizeof(struct sbar));
newptr = reallocarray(ptr, 500, sizeof(struct sbar));
```

#### Реалізація
```c
void task_4_7() {
    struct sbar *ptr = calloc(1000, sizeof(struct sbar));
    struct sbar *newptr = reallocarray(ptr, 500, sizeof(struct sbar));
    
    if (newptr == NULL) {
        perror("Помилка reallocarray");
        free(ptr);
    }
}
```

#### Очікувані результати
- `reallocarray()` успішно перевиділить пам'ять для 500 елементів
- Переповнення при множенні буде перевірено

### Завдання 6: Стрес-тестування `malloc()`
#### Опис
Тестування поведінки `malloc()` при виділенні великих обсягів пам'яті та при високому навантаженні.

#### Реалізація
```c
void large_memory_allocation_test() {
    size_t sizes[] = {
        100 * MB,     // 100 МБ
        500 * MB,     // 500 МБ
        1 * GB,       // 1 ГБ
        2 * GB,       // 2 ГБ
        4 * GB        // 4 ГБ
    };
    
    for (int i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
        clock_t start, end;
        double cpu_time_used;
        
        printf("\nВиділення %zu байтів\n", sizes[i]);
        
        start = clock();
        void *ptr = malloc(sizes[i]);
        end = clock();
        
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        
        if (ptr == NULL) {
            printf("Помилка виділення пам'яті\n");
            perror("malloc");
            continue;
        }
        
        memset(ptr, 0, sizes[i]);
        
        printf("Успішно виділено. Час виділення: %f сек\n", cpu_time_used);
        
        free(ptr);
    }
}
```

#### Очікувані результати
- Успішне виділення малих і середніх блоків пам'яті
- Можливі помилки при виділенні дуже великих блоків
- Залежність часу виділення від розміру блоку
- Системні обмеження можуть відрізнятися на різних платформах

## Вимоги
- Компілятор GCC
- Операційна система Linux

## Компіляція та запуск

### Базова компіляція
```bash
gcc -o memory_tasks src/memory_tasks.c -Wall -Wextra
```

### Запуск програми
```bash
./memory_tasks
```

### Компіляція тестів на високе навантаження
```bash
gcc -o memory_stress src/memory_stress.c -Wall -Wextra
```

## Аналіз результатів
Після запуску тестів рекомендується проаналізувати такі аспекти:
1. Чи відповідає поведінка функцій документації C
2. Чи правильно обробляються помилки
3. Які системні обмеження впливають на виділення пам'яті
4. Як змінюється час виділення в залежності від розміру блоку
5. Чи є відмінності між різними системами та архітектурами
