#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

#define MSG_SIZE 100

// Message structure
struct message {
    long msg_type;       // Message type
    char msg_text[MSG_SIZE]; // Message content
};

int main() {
    pid_t pid;
    key_t key;
    int msgid;

    // Generate a unique key for the message queue
    key = ftok("progfile", 65);
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    pid = fork(); // Create child process

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) { // Child process
        struct message msg;
        // Receive a message from the parent
        if (msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0) == -1) {
            perror("msgrcv failed");
            exit(1);
        }
        printf("Child received: %s\n", msg.msg_text);

        // Send a response to the parent
        msg.msg_type = 2; // Message type for parent
        strcpy(msg.msg_text, "Hello, Parent!");
        if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
            perror("msgsnd failed");
            exit(1);
        }
    } else { // Parent process
        struct message msg;
        // Send a message to the child
        msg.msg_type = 1; // Message type for child
        strcpy(msg.msg_text, "Hello, Child!");
        if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
            perror("msgsnd failed");
            exit(1);
        }

        // Wait for a response from the child
        if (msgrcv(msgid, &msg, sizeof(msg.msg_text), 2, 0) == -1) {
            perror("msgrcv failed");
            exit(1);
        }
        printf("Parent received: %s\n", msg.msg_text);

        // Clean up the message queue
        if (msgctl(msgid, IPC_RMID, NULL) == -1) {
            perror("msgctl failed");
            exit(1);
        }
    }

    return 0;
}
