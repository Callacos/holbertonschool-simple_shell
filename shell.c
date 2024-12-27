#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "shell.h"


/**
 * find_executable - Finds the full path of an executable command
 * @command: The command to find
 *
 * Return: The full path of the executable command, or NULL if not found
 */
char *find_executable(char *command)
{
char *path = getenv("PATH");
char *path_copy = strdup(path);
char *dir = strtok(path_copy, ":");
char *full_path = NULL;

while (dir != NULL)
{
	full_path = malloc(strlen(dir) + strlen(command) + 2);
	if (!full_path)
	{
		perror("malloc");
		free(path_copy);
		return (NULL);
	}
	strcpy(full_path, dir);
	strcat(full_path, "/");
	strcat(full_path, command);

	if (access(full_path, X_OK) == 0)
	{
		free(path_copy);
		return (full_path);
	}

	free(full_path);
	full_path = NULL;
	dir = strtok(NULL, ":");
}

free(path_copy);
return (NULL);
}

/**
 * execute_command - Executes a command by finding its full path and running it
 * @command: The command to execute
 */
void execute_command(char *command)
{
char *path_command = find_executable(command);

if (path_command != NULL)
{
	char *args[] = {path_command, NULL};

	if (execve(path_command, args, environ) == -1)
	{
		perror("Error");
		free(path_command);
		exit(EXIT_FAILURE);
	}
	free(path_command);
}
else
{
	fprintf(stderr, "Command not found: %s\n", command);
	exit(EXIT_FAILURE);
}
}

/**
 * shell_loop - Main loop of the shell
 */
void shell_loop(void)
{
char *command = NULL;
size_t len = 0;
ssize_t read;

while (1)
{
	printf("callayass_shell$ ");
	read = getline(&command, &len, stdin);
	if (read == -1)
		break;

	command[strcspn(command, "\n")] = '\0';

	if (strlen(command) == 0)
		continue;

	if (strcmp(command, "exit") == 0)
	{
		free(command);
		exit(0);

	}
		break;

	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		continue;
	}
	if (pid == 0)
	{
		execute_command(command);
	}
	else
	{
		wait(NULL);
	}
}
free(command);
}

/**
 * main - Entry point of the shell program
 * @ac: Argument count (unused)
 * @av: Argument vector
 *
 * Return: Always 0
 */
int main(__attribute__((unused)) int ac, char **av)
{
shell_loop();
return (0);
}
