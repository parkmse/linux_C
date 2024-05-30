#include <stdio.h>

void primeFactorization(int num);

int main() {
    int num;
    printf("Input integer: ");
    scanf("%d", &num);
    primeFactorization(num);
    return 0;
}

void primeFactorization(int num) {
    int i;
    for (i = 2; i <= num; i++) {
        while (num % i == 0) {
            printf("%d ", i);
            num /= i;
        }
    }
}

