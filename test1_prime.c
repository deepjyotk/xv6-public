#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    int pid1 = fork();
    if (pid1 == 0) {
        nice(getpid(), 1); // Highest priority
        printf(1, "high priority process\n");
        
        char *args[] = { "prime", 0 };
        if (exec("prime", args) < 0) {
            printf(1, "Error: exec failed for prime\n");
        }
        exit();
    }

    int pid2 = fork();
    if (pid2 == 0) {
        nice(getpid(), 5); // Lowest priority
        printf(1, "low priority process 1\n");
        
        char *args[] = { "prime", 0 };
        if (exec("prime", args) < 0) {
            printf(1, "Error: exec failed for prime\n");
        }
        exit();
    }

    int pid3 = fork();
    if (pid3 == 0) {
        nice(getpid(), 5); // Lowest priority
        printf(1, "low priority process 2\n");
        
        char *args[] = { "prime", 0 };
        if (exec("prime", args) < 0) {
            printf(1, "Error: exec failed for prime\n");
        }
        exit();
    }

    wait();
    wait();
    wait();
    exit();
}