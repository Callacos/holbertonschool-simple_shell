#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "shell.h"

void custom_exit(char **args);
int print_env(char **env);

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
	} else if (chdir(args[1]) != 0)
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
	if (execvp(args[0], args) == -1)
	{
		perror("Erreur d'exécution");
		exit(127);
	}
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
