#include <stdio.h>

/**
 * main - Affiche les arguments passés en ligne de commande sans utiliser 'ac'
 * @av: Tableau des arguments
 *
 * Return: 0 si succès
 */
int main(__attribute__((unused)) char **av)
{
	int i = 0;

	while (av[i] != NULL)
	{
		printf("Argument %d : %s\n", i, av[i]);
		i++;
	}

	return (0);
}
