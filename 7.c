#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     // For fork(), execv()
#include <sys/types.h>  // For pid_t
#include <sys/wait.h>   // For waitpid()

#define MAX_LINE_LENGTH 1024
#define MAX_ARGS 20

int main() {
    char line[MAX_LINE_LENGTH];

    while (1) {
        // Prompt the user
        printf("shell> ");
        fflush(stdout);

        // Read the input line
        if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL) {
            // EOF encountered (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove the newline character from the end of the line
        line[strcspn(line, "\n")] = '\0';

        // Check for empty input
        if (line[0] == '\0') {
            continue;
        }

        // Check for exit command
        if (strcmp(line, "exit") == 0) {
            break;
        }

        // Parse the line into arguments
        char *argv[MAX_ARGS];
        int argc = 0;

        char *token = strtok(line, " ");
        while (token != NULL && argc < MAX_ARGS - 1) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL;  // NULL-terminate the argument list

        // Fork a child process
        pid_t pid = fork();
        if (pid < 0) {
            // Error in fork
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // Child process
            // Execute the command (full pathname assumed)
            execv(argv[0], argv);
            // If execv returns, an error occurred
            perror("execv");
            exit(1);
        } else {
            // Parent process
            // Wait for the child process to complete
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
