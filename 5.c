#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;

    // Fork the first child process
    pid1 = fork();
    if (pid1 < 0) {
        // Error occurred during fork
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // Inside the first child process

        // Fork the second child (grandchild)
        pid2 = fork();
        if (pid2 < 0) {
            // Error occurred during fork
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) {
            // Inside the second child (grandchild) process
            // Execute the 'ps' command
            execlp("ps", "ps", NULL);
            // If execlp returns, an error occurred
            perror("execlp");
            exit(EXIT_FAILURE);
        } else {
            // First child process waits for the grandchild to finish
            wait(NULL);
            exit(EXIT_SUCCESS);
        }
    } else {
        // Parent process waits for the first child to finish
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
}
