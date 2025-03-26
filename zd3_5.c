#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/stat.h>

void set_file_size_limit(int max_size_mb) {
    struct rlimit rlim;
    rlim.rlim_cur = max_size_mb * 1024 * 1024;
    rlim.rlim_max = max_size_mb * 1024 * 1024;

    if (setrlimit(RLIMIT_FSIZE, &rlim) == -1) {
        perror("Помилка встановлення обмеження розміру файлу");
    }
}

int copy_file(const char* source, const char* destination) {
    if (source == NULL || destination == NULL) {
        printf("Program need two arguments\n");
        return -1;
    }
    
    FILE* src_file = fopen(source, "rb");
    if (src_file == NULL) {
        printf("Cannot open file %s for reading\n", source);
        return -1;
    }
    
    FILE* dest_file = fopen(destination, "wb");
    if (dest_file == NULL) {
        printf("Cannot open file %s for writing\n", destination);
        fclose(src_file);
        return -1;
    }
    
    set_file_size_limit(10);  // 10 МБ
    
    int ch;
    while ((ch = fgetc(src_file)) != EOF) {
        if (fputc(ch, dest_file) == EOF) {
            perror("Помилка запису у файл");
            fclose(src_file);
            fclose(dest_file);
            return -1;
        }
    }
    
    fclose(src_file);
    fclose(dest_file);
    
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Program need two arguments\n");
        return -1;
    }
    
    return copy_file(argv[1], argv[2]);
}
