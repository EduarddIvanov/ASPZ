#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double random_0_to_1() {
    return (double)rand() / RAND_MAX;
}

double random_0_to_n(double n) {
    return ((double)rand() / RAND_MAX) * n;
}

int main() {
    double n;
    int i;
    
    srand(time(NULL));
    
    printf("Random numbers from 0.0 to 1.0:\n");
    for (i = 0; i < 10; i++) {
        printf("%.6f\n", random_0_to_1());
    }
    
    printf("\nEnter n for range 0.0 to n: ");
    scanf("%lf", &n);
    
    printf("Random numbers from 0.0 to %.2f:\n", n);
    for (i = 0; i < 10; i++) {
        printf("%.6f\n", random_0_to_n(n));
    }
    
    return 0;
}
