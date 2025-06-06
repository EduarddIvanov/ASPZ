#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char response[10];
    
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
        
        if (S_ISREG(file_stat.st_mode)) {
            printf("Delete file '%s'? (y/n): ", entry->d_name);
            fgets(response, sizeof(response), stdin);
            
            if (response[0] == 'y' || response[0] == 'Y') {
                if (unlink(entry->d_name) == -1) {
                    perror("unlink");
                } else {
                    printf("File '%s' deleted.\n", entry->d_name);
                }
            }
        }
    }
    
    closedir(dir);
    return 0;
}
