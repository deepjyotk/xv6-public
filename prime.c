#include "types.h"
#include "stat.h"
#include "user.h"

#define MAXPRIMELIMIT 200

int isPrime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

void print_primes() {
    for (int i = 1; i <= MAXPRIMELIMIT; i++) {
        if (isPrime(i)) {
            printf(1, "%d ", i);
            for (volatile int j = 0; j < 1000000; j++);
        }
    }
    printf(1, "\n");
}

int main() {
    print_primes();
    exit();
}