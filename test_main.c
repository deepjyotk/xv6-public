#include "types.h"
#include "stat.h"
#include "user.h"

void test_set_nice_for_pid() {
    printf(1, "Scenario 1: Modifying nice value for PID 1\n");
    nice(1, 3); // setting default nice value of PID 1 to 3
    int previous = nice(1, 4);
    printf(1, "Expected Outcome:\tPID 1, Previous value 3 (default is 3)\n");
    printf(1, "Result:\t\t\tPID 1, Previous value %d\n\n", previous);
}

void test_adjust_self_nice() {
    printf(1, "Scenario 2: Adjusting nice value for current process\n");
    int current_pid = getpid();
    int previous = nice(current_pid, 2);
    printf(1, "Expected Outcome:\tPID %d, Previous value 3 (default is 3)\n", current_pid);
    printf(1, "Result:\t\t\tPID %d, Previous value %d\n\n", current_pid, previous);
}

void test_nice_value_below_min() {
    printf(1, "Scenario 3: Attempting below-bound nice value\n");
    int outcome = nice(1, 0);
    printf(1, "Expected Outcome:\tError: Nice value must range from 1 to 5\n");
    printf(1, "Result:\t\t\t%s\n\n", 
           (outcome == -2) ? "Error: Nice value must range from 1 to 5" : 
           (outcome < 0) ? "Error: Invalid PID or Value" : "Unexpected success");
}

void test_nice_value_above_max() {
    printf(1, "Scenario 4: Attempting above-bound nice value\n");
    int outcome = nice(1, 6);
    printf(1, "Expected Outcome:\tError: Nice value must range from 1 to 5\n");
    printf(1, "Result:\t\t\t%s\n\n", 
           (outcome == -2) ? "Error: Nice value must range from 1 to 5" : 
           (outcome < 0) ? "Error: Invalid PID or Value" : "Unexpected success");
}

void test_nonexistent_process() {
    printf(1, "Scenario 5: Changing nice value for a nonexistent PID\n");
    int result = nice(9999, 3);
    printf(1, "Expected Outcome:\tError: Invalid PID or Value\n");
    printf(1, "Result:\t\t\t%s\n\n", (result < 0) ? "Error: Invalid PID or Value" : "Unexpected success");
}

void test_repeated_nice_adjustments() {
    printf(1, "Scenario 6: Applying multiple nice adjustments\n");
    int current_pid = getpid();
    int first_result = nice(current_pid, 2);
    int second_result = nice(current_pid, 4);
    printf(1, "Expected Outcome:\tFirst adjustment - PID %d, Previous value 3; Second adjustment - PID %d, Previous value 2\n", current_pid, current_pid);
    printf(1, "Result:\t\t\tFirst adjustment - PID %d, Previous value %d; Second adjustment - PID %d, Previous value %d\n\n", current_pid, first_result, current_pid, second_result);
}

void initiate_test(void (*test_case)()) {
    if (fork() == 0) {
        test_case();
        exit();
    } else {
        wait();
    }
}

int main() {
    printf(1, "Initiating tests for nice system call\n\n");

    initiate_test(test_set_nice_for_pid);
    initiate_test(test_adjust_self_nice);
    initiate_test(test_nice_value_below_min);
    initiate_test(test_nice_value_above_max); 
    initiate_test(test_nonexistent_process);
    initiate_test(test_repeated_nice_adjustments);
    
    printf(1, "All test cases have been executed\n");
    exit();
}
