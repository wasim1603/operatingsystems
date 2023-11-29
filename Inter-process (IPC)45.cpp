#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MSG_SIZE 1024

// Define a structure for the message
struct Message {
    long msg_type;
    char msg_text[MAX_MSG_SIZE];
};

int main() {
    int msgid;
    struct Message message;

    key_t key = ftok("message_queue_key", 'A'); // Generate a unique key for the message queue
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a message queue
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Parent process sends a message to the queue
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {  // Child process reads the message from the queue
        if (msgrcv(msgid, &message, MAX_MSG_SIZE, 1, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
        printf("Received message in child process: %s\n", message.msg_text);
    } else {  // Parent process writes a message to the queue
        strcpy(message.msg_text, "Hello, Message Queue!");
        message.msg_type = 1;

        if (msgsnd(msgid, &message, sizeof(message), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
        printf("Sent message from parent process\n");

        // Wait for the child to finish
        wait(NULL);

        // Remove the message queue
        if (msgctl(msgid, IPC_RMID, NULL) == -1) {
            perror("msgctl");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

