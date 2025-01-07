#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "shell.h"

void custom_exit(char **args);

/**
 * main - Point d'entrée du programme shell
 *
 * Return: Toujours 0 (Succès)
 */
int main(void)
{
char command[1024];
char *args[10];
pid_t pid;
int i;

while (1)
{
    printf("callayass_shell$ ");
    if (fgets(command, sizeof(command), stdin) == NULL)
        break;

    command[strcspn(command, "\n")] = '\0';

    /* Analyse des arguments */
    i = 0;
    args[i] = strtok(command, " \t");
    while (args[i] != NULL && i < 9)
    {
        args[++i] = strtok(NULL, " \t");
    }
    args[i] = NULL;

    /* Vérification de la commande exit */
    if (args[0] != NULL && strcmp(args[0], "exit") == 0)
    {
        custom_exit(args);
    }

    pid = fork();
    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("Erreur");
            exit(EXIT_FAILURE);
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

return (0);
}
