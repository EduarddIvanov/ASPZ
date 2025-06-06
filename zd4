#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char line[1024];
    int line_count = 0;
    int i;
    
    if (argc < 2) {
        printf("Usage: %s <filename1> [filename2] ...\n", argv[0]);
        exit(1);
    }
    
    for (i = 1; i < argc; i++) {
        file = fopen(argv[i], "r");
        if (file == NULL) {
            perror("fopen");
            continue;
        }
        
        printf("==> %s <==\n", argv[i]);
        line_count = 0;
        
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
            line_count++;
            
            if (line_count % 20 == 0) {
                printf("-- Press any key to continue --");
                getchar();
            }
        }
        
        fclose(file);
        printf("\n");
    }
    
    return 0;
}
