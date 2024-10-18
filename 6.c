#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int status;

    // Ensure at least one argument is provided (the command to execute)
    if (argc < 2) {
        fprintf(stderr, "Usage: %s command [arguments...]\n", argv[0]);
        return 1;
    }

    // Create a new child process
    pid = fork();

    if (pid == -1) {
        // Error occurred during fork()
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // In the child process: execute the command with given arguments
        execvp(argv[1], &argv[1]);
        // If execvp returns, an error has occurred
        perror("execvp");
        return 1;
    } else {
        // In the parent process: wait for the child process to complete
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            return 1;
        }
        // Optionally, check how the child process terminated
        if (WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child terminated abnormally\n");
        }
    }

    return 0;
}
