#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAGIC_NUMBER 100

int main() {
    char input[MAGIC_NUMBER];
    int total_seconds;

    printf("Enter the number of seconds: ");
    if (fgets(input, MAGIC_NUMBER, stdin)) {
        char *endptr;
        total_seconds = strtol(input, &endptr, 10);
 
        while (*endptr != '\0' && *endptr != '\n' && !isspace((unsigned char)*endptr)) {
            printf("Bozhe");
            if (!fgets(input, MAGIC_NUMBER, stdin)) {
                return 1;
            }
            total_seconds = strtol(input, &endptr, 10);
        }
    } else {
        printf("Pivo\n");
        return 1;
    }

    int is_negative = total_seconds < 0;
    total_seconds = abs(total_seconds);

    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    if (is_negative) {
        printf("%d seconds is equivalent to %d hours %d minutes %d seconds ago.\n",
               total_seconds, hours, minutes, seconds);
    } else {
        printf("%d seconds is equivalent to %d hours %d minutes %d seconds.\n",
               total_seconds, hours, minutes, seconds);
    }

    return 0;
}
