#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10
#define MAX_PATH_LENGTH 1024

void execute_command(char *argv[], char **envp) {
	char *path = getenv("PATH");
	char full_command[MAX_PATH_LENGTH];
	char *path_token = strtok(path, ":");

	while (path_token != NULL) {
		snprintf(full_command, MAX_PATH_LENGTH, "%s/%s", path_token, argv[0]);
		if (access(full_command, X_OK) == 0) {
			argv[0] = full_command;
			execve(full_command, argv, envp);
			return;
		}
		path_token = strtok(NULL, ":");
	}

	fprintf(stderr, "%s: command not found\n", argv[0]);
	exit(EXIT_FAILURE);
}

int main(void) {
	char command[MAX_COMMAND_LENGTH];
	char *argv[MAX_ARGS];
	char *token;
	int i;

	while (1) {
		printf("#cisfun$ ");
		fflush(stdout);

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
			printf("\n");
			continue;
		}

		if (command[strlen(command) - 1] == '\n') {
			command[strlen(command) - 1] = '\0';
		}

		if (strcmp(command, "exit") == 0) {
			break;
		}

		i = 0;
		token = strtok(command, " ");
		while (token != NULL && i < MAX_ARGS - 1) {
			argv[i++] = token;
			token = strtok(NULL, " ");
		}
		argv[i] = NULL;

		if (argv[0] != NULL) {
			if (fork() == 0) {
				execute_command(argv, environ);
			} else {
				wait(NULL);
			}
		}
	}

	return (0);
}
