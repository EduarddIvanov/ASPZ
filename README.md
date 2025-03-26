# ASPZ
# Дослідження сегментів пам'яті в Linux

## Опис проекту

Дослідження сегментів пам'яті Linux.

## Структура проекту

- `time_t_overflow.c`: Дослідження переповнення типу `time_t`
- `segment_research.c`: Аналіз різних сегментів пам'яті
- `stack_top.c`: Вивчення структури стека
- `recursive_stack_size.c`: Визначення мінімального розміру стека для рекурсії

## Вимоги

- Компілятор GCC
- Операційна система Linux

## Компіляція та запуск

### Компіляція базової версії

```bash
gcc -o segment_research segment_research.c
gcc -o time_t_overflow time_t_overflow.c
gcc -o stack_top stack_top.c
gcc -o recursive_stack_size recursive_stack_size.c
```

### Компіляція з різними режимами

#### Налагодження
```bash
gcc -g -o segment_research_debug segment_research.c
```

#### Максимальна оптимізація
```bash
gcc -O3 -o segment_research_optimized segment_research.c
```

## Дослідження

### 1. Розміри сегментів

Команди:

```bash
size segment_research
```

### 2. Аналіз символів

```bash
nm segment_research
objdump -h segment_research
```

## Очікувані результати

- Сегмент BSS не займає місця у файлі
- Ініційовані масиви розміщуються в сегменті даних
- Локальні масиви розміщуються в стеку
- Текстовий сегмент оптимізується компілятором

## Інші команди

```bash
# Перегляд інформації про виконуваний файл
file segment_research

# Перевірка залежностей
ldd segment_research
```
