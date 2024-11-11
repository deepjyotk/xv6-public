// test5.c
#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    int pid = fork();
    if (pid == 0) {
        nice(getpid(), 5); // Start with lowest priority
        printf(1, "process starting with lowest priority\n");

        sleep(50); // Allow other processes to run, simulate workload
        nice(getpid(), 1); // Increase to highest priority after sleep
        printf(1, "process changed to highest priority\n");

        char *args[] = { "prime", 0 };
        if (exec("prime", args) < 0) {
            printf(1, "Error: exec failed for prime\n");
        }
        exit();
    }

    wait();
    exit();
}