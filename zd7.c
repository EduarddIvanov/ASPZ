#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char response[10];
    int len;
    
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        exit(1);
    }
    
    while ((entry = readdir(dir)) != NULL) {
        len = strlen(entry->d_name);
        if (len < 2 || strcmp(entry->d_name + len - 2, ".c") != 0)
            continue;
            
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat");
            continue;
        }
        
        printf("C source file: %s\n", entry->d_name);
        printf("Current permissions: ");
        printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
        printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
        printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
        printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
        printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
        printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
        printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
        printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
        printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
        printf("\n");
        
        printf("Give others read permission? (y/n): ");
        fgets(response, sizeof(response), stdin);
        
        if (response[0] == 'y' || response[0] == 'Y') {
            if (chmod(entry->d_name, file_stat.st_mode | S_IROTH) == -1) {
                perror("chmod");
            } else {
                printf("Permission granted.\n");
            }
        }
        printf("\n");
    }
    
    closedir(dir);
    return 0;
}
