#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char *directories[1000];
    int dir_count = 0;
    int i;
    
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        exit(1);
    }
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
            
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat");
            continue;
        }
        
        if (S_ISDIR(file_stat.st_mode)) {
            directories[dir_count] = malloc(strlen(entry->d_name) + 1);
            strcpy(directories[dir_count], entry->d_name);
            dir_count++;
        }
    }
    
    closedir(dir);
    
    qsort(directories, dir_count, sizeof(char*), compare_strings);
    
    for (i = 0; i < dir_count; i++) {
        printf("%s\n", directories[i]);
        free(directories[i]);
    }
    
    return 0;
}
