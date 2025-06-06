#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char line[1024];
    char *search_word;
    
    if (argc < 3) {
        printf("Usage: %s <word> <filename>\n", argv[0]);
        exit(1);
    }
    
    search_word = argv[1];
    file = fopen(argv[2], "r");
    
    if (file == NULL) {
        perror("fopen");
        exit(1);
    }
    
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, search_word) != NULL) {
            printf("%s", line);
        }
    }
    
    fclose(file);
    return 0;
}
