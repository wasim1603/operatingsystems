#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024  // Size of the shared memory segment

int main() {
    int shmid;
    key_t key;
    char *shm_ptr;

    // Generate a unique key for the shared memory segment
    key = ftok("shared_memory_key", 'R');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a shared memory segment
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory segment to the process's address space
    shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (char *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Write data to the shared memory
    sprintf(shm_ptr, "Hello, Shared Memory!");

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {  // Child process
        printf("Child process reads from shared memory: %s\n", shm_ptr);

        // Detach the shared memory segment from the child process
        if (shmdt(shm_ptr) == -1) {
            perror("shmdt");
            exit(EXIT_FAILURE);
        }
    } else {  // Parent process
        // Wait for the child to finish
        wait(NULL);

        printf("Parent process reads from shared memory: %s\n", shm_ptr);

        // Detach the shared memory segment from the parent process
        if (shmdt(shm_ptr) == -1) {
            perror("shmdt");
            exit(EXIT_FAILURE);
        }

        // Remove the shared memory segment
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

