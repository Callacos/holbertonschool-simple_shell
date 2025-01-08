#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "shell.h"

void custom_exit(char **args);
int print_env(char **env);
char *locate_executable(char *command, char *path);

/**
 * main - Point d'entrée du programme shell
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: Environment variables
 *
 * Return: Toujours 0 (Succès)
 */
int main(int argc, char *argv[], char **envp)
{
char *command = NULL;
char *args[20];
size_t bufsize = 0;
ssize_t characters;
pid_t pid;
int i;

(void)argc;
(void)argv;

while (1)
{
	if (isatty(STDIN_FILENO))
		printf("callayass_shell$ ");

	characters = getline(&command, &bufsize, stdin);
	if (characters == -1)
	{
		if (isatty(STDIN_FILENO))
			printf("\n");
		break;
	}

	command[strcspn(command, "\n")] = '\0';

	i = 0;
	args[i] = strtok(command, " \t");
	while (args[i] != NULL && i < 19)
	{
		args[++i] = strtok(NULL, " \t");
	}
	args[i] = NULL;

	if (args[0] == NULL)
		continue;

	if (strcmp(args[0], "exit") == 0)
	{
		custom_exit(args);
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		if (args[1] == NULL)
		{
			fprintf(stderr, "cd: missing argument\n");
		}
		else if (chdir(args[1]) != 0)
		{
			perror("cd");
		}
		continue;
	}
	else if (strcmp(args[0], "env") == 0)
	{
		print_env(envp);
		continue;
	}

	pid = fork();
	if (pid == 0)
	{
		/* Locate executable using PATH */
		char *path = getenv("PATH");
		char *full_path = locate_executable(args[0], path);

		if (full_path == NULL || execve(full_path, args, envp) == -1)
		{
			perror("Erreur d'exécution");
			free(full_path);
			exit(127);
		}
		free(full_path);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
	else
	{
		perror("Erreur de fork");
	}
}

free(command);
return (0);
}

/**
 * print_env - Prints the environment variables
 * @env: The environment variables
 *
 * Return: Always 0 (Success)
 */
int print_env(char **env)
{
int i = 0;

while (env[i])
{
	printf("%s\n", env[i++]);
}
return (0);
}

/**
 * locate_executable - Finds the full path of a command using PATH
 * @command: The command to find
 * @path: The PATH environment variable
 *
 * Return: Full path of the executable, or NULL if not found
 */
char *locate_executable(char *command, char *path)
{
char *dir, *full_path;
size_t len;

if (command[0] == '/' || command[0] == '.')
	return (strdup(command));

dir = strtok(path, ":");
while (dir != NULL)
{
	len = strlen(dir) + strlen(command) + 2;
	full_path = malloc(len);
	if (full_path == NULL)
		return (NULL);

	snprintf(full_path, len, "%s/%s", dir, command);
	if (access(full_path, X_OK) == 0)
		return (full_path);

	free(full_path);
	dir = strtok(NULL, ":");
}
return (NULL);
}
