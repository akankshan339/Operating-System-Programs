#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64
#define DELIM " \t\r\n\a"

// Function to tokenize input
void tokenize_input(char *input, char **args) {
    char *token = strtok(input, DELIM);
    int index = 0;
    while (token != NULL) {
        args[index++] = token;
        token = strtok(NULL, DELIM);
    }
    args[index] = NULL;
}

// Built-in command: cd
void shell_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "cd: expected argument\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }
}

// Built-in command: exit
void shell_exit() {
    exit(0);
}

// Built-in command: cat
void shell_cat(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "cat: expected argument\n");
        return;
    }

    FILE *src = fopen(args[1], "r");
    if (src == NULL) {
        perror("cat");
        return;
    }

    if (args[2] != NULL) {
        FILE *dest = fopen(args[2], "w");
        if (dest == NULL) {
            perror("cat");
            fclose(src);
            return;
        }
        char buffer[1024];
        size_t bytes;
        while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
            fwrite(buffer, 1, bytes, dest);
        }
        fclose(dest);
    } else {
        char ch;
        while ((ch = fgetc(src)) != EOF) {
            putchar(ch);
        }
    }
    fclose(src);
    printf("\n");
}

// Built-in command: mv
void shell_mv(char **args) {
    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "mv: expected source and destination\n");
        return;
    }
    if (rename(args[1], args[2]) != 0) {
        perror("mv");
    }
}

// Built-in command: ls
void shell_ls() {
    pid_t pid = fork();
    if (pid == 0) {
        execlp("ls", "ls", NULL);
        perror("ls");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork");
    }
}

// Execute external commands
void execute_command(char **args) {
    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("Command execution failed");
        }
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork");
    }
}

// Main shell loop
void shell_loop() {
    char input[MAX_INPUT];
    char *args[MAX_ARGS];

    while (1) {
        printf("myshell> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        if (strcmp(input, "\n") == 0) continue;

        input[strcspn(input, "\n")] = '\0'; // Remove trailing newline
        tokenize_input(input, args);

        if (strcmp(args[0], "exit") == 0) {
            shell_exit();
        } else if (strcmp(args[0], "cd") == 0) {
            shell_cd(args);
        } else if (strcmp(args[0], "cat") == 0) {
            shell_cat(args);
        } else if (strcmp(args[0], "mv") == 0) {
            shell_mv(args);
        } else if (strcmp(args[0], "ls") == 0) {
            shell_ls();
        } else {
            execute_command(args);
        }
    }
}

int main() {
    shell_loop();
    return 0;
}