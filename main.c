#include "shell.h"

#define MAX_INPUT_SIZE 1024

void execute_command(char *command) {
    /* Declare pid_t at the beginning of the block */
    pid_t pid;

    /* Tokenize the command */
    char *args[MAX_INPUT_SIZE];
    char *token = strtok(command, " \t\n");
    int i = 0;

    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }

    args[i] = NULL;

    /* Fork a child process */
    pid = fork();

    if (pid == 0) {
        /* Child process */
        if (execvp(args[0], args) == -1) {
            perror("Error executing command");
        }
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        /* Parent process */
        wait(NULL); /* Wait for the child process to complete */
    } else {
        perror("Error forking process");
    }
}

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        /* Display the prompt */
        printf("$ ");
        fflush(stdout);

        /* Read user input */
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; /* Exit on EOF (e.g., Ctrl+D) */
        }

        /* Remove the newline character */
        input[strcspn(input, "\n")] = '\0';

        /* Exit the shell if the user enters "exit" or "quit" */
        if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
            break;
        }

        /* Execute the command */
        execute_command(input);
    }

    return 0;
}

