# Set of solved process management and command/program execution problems in the Unix/Linux operating system

4: Creates a new child process using fork(). The child process then replaces its image with the ls program using execlp(), which is one of the exec() family of functions. The parent process waits for the child to complete.

5: Creates a new child process, which in turn creates another child process. The grandchild process executes the ps command to display the processes running on the system. Each fork call is checked for errors, and the parent processes wait for their respective child processes to finish before exiting.

6: Creates a child process that executes the command provided as arguments to main().

7: A simple shell that prompts the user for a command (or executable) to execute. It reads the input, parses it using strtok(), stores the tokens in the argv[] array (including a NULL pointer at the end), and then executes the command assuming the command name contains the full pathname.

### Dependencies

* C and Linux/Unix Operating System.
