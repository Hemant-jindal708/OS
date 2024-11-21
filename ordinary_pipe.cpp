#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 256

int main() {
    int pipe1[2]; // Pipe for parent to child
    int pipe2[2]; // Pipe for child to parent
    pid_t pid;

    // Create the pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

    pid = fork(); // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) { // Child process
        close(pipe1[1]); // Close the write end of pipe1
        close(pipe2[0]); // Close the read end of pipe2

        char buffer[BUFFER_SIZE];
        read(pipe1[0], buffer, BUFFER_SIZE); // Read from parent
        printf("Child received: %s\n", buffer);

        // Respond to parent
        char response[] = "Hello, Parent!";
        write(pipe2[1], response, strlen(response) + 1);

        close(pipe1[0]);
        close(pipe2[1]);
    } else { // Parent process
        close(pipe1[0]); // Close the read end of pipe1
        close(pipe2[1]); // Close the write end of pipe2

        // Send a message to the child
        char message[] = "Hello, Child!";
        write(pipe1[1], message, strlen(message) + 1);

        // Wait for a response from the child
        char buffer[BUFFER_SIZE];
        read(pipe2[0], buffer, BUFFER_SIZE);
        printf("Parent received: %s\n", buffer);

        close(pipe1[1]);
        close(pipe2[0]);
    }

    return 0;
}
