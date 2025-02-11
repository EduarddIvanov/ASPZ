#include <stdio.h>
#include <stdlib.h>

int main() {
    int total_seconds;

    printf("Enter the number of seconds: ");
    scanf("%d", &total_seconds);

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


