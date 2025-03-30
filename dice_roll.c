#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <errno.h>

void set_file_size_limit(int max_size_mb) {
    struct rlimit rlim;
    rlim.rlim_cur = max_size_mb * 1024 * 1024;
    rlim.rlim_max = max_size_mb * 1024 * 1024;

    if (setrlimit(RLIMIT_FSIZE, &rlim) == -1) {
        perror("Помилка встановлення обмеження розміру файлу");
    }
}

void simulate_dice_rolls(const char* filename, int num_rolls, int max_size_mb) {
    set_file_size_limit(max_size_mb);
    
    srand(time(NULL));
    FILE* file = fopen(filename, "w");
    
    if (file == NULL) {
        perror("Помилка відкриття файлу");
        return;
    }
    
    for (int i = 0; i < num_rolls; i++) {
        int roll = rand() % 6 + 1;
        fprintf(file, "Кидок кубика: %d\n", roll);
    }
    
    fclose(file);
}

int main() {
    simulate_dice_rolls("dice_rolls.txt", 1000, 1);
    return 0;
}
