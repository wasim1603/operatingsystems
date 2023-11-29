#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        printf("Child Process:\n");
        printf("PID: %d\n", getpid());
        printf("Parent's PID: %d\n", getppid());
    } else {
        printf("Parent Process:\n");
        printf("PID: %d\n", getpid());
        printf("Child's PID: %d\n", pid);
    }

    return 0;
}

