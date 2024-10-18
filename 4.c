#include <stdio.h>
#include <stdlib.h>    // For exit()
#include <unistd.h>    // For fork(), execlp()
#include <sys/types.h> // For pid_t
#include <sys/wait.h>  // For wait()

int main() {
    pid_t pid = fork(); // Create a new child process

    if (pid < 0) {
        // Fork failed
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        execlp("ls", "ls", (char *)NULL); // Execute 'ls' using exec()
        // If execlp returns, an error occurred
        perror("execlp failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        wait(NULL); // Wait for the child process to finish
    }

    return 0;
}
