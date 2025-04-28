#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_USERS 100
#define MAX_FILENAME 256
#define THRESHOLD 3 

typedef struct {
    char filename[MAX_FILENAME];
    int user_ids[MAX_USERS];
    int user_count;
} FileUsage;

int is_user_in_list(int user_ids[], int count, int user_id) {
    for (int i = 0; i < count; i++) {
        if (user_ids[i] == user_id) {
            return 1;
        }
    }
    return 0;
}

void change_permissions(const char *filename, mode_t mode) {
    if (chmod(filename, mode) == -1) {
        perror("chmod error");
    } else {
        printf("Permissions changed for %s\n", filename);
    }
}

int main() {
    FILE *log = fopen("usage.log", "r");
    if (!log) {
        perror("Unable to open usage log");
        return 1;
    }

    FileUsage files[100];
    int file_count = 0;

    char file[MAX_FILENAME];
    int user_id;

    while (fscanf(log, "%s %d", file, &user_id) == 2) {
        int found = 0;
        for (int i = 0; i < file_count; i++) {
            if (strcmp(files[i].filename, file) == 0) {
                if (!is_user_in_list(files[i].user_ids, files[i].user_count, user_id)) {
                    files[i].user_ids[files[i].user_count++] = user_id;
                }
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(files[file_count].filename, file);
            files[file_count].user_ids[0] = user_id;
            files[file_count].user_count = 1;
            file_count++;
        }
    }

    fclose(log);

    for (int i = 0; i < file_count; i++) {
        if (files[i].user_count >= THRESHOLD) {
            change_permissions(files[i].filename, 0644); // більш відкрите
        } else {
            change_permissions(files[i].filename, 0600); // обмежене
        }
    }

    return 0;
}
