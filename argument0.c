#include <stdio.h>

/**
 * args - Affiche les arguments passés en ligne de commande sans utiliser 'ac'
 * @argc: Nombre d'arguments (non utilisé)
 * @argv: Tableau des arguments
 *
 * Return: 0 si succès
 */
int args(int argc, char **argv)
{
int i = 0;

(void)argc;  /* Marquer argc comme non utilisé */

while (argv[i] != NULL)
{
	printf("Argument %d : %s\n", i, argv[i]);
	i++;
}

return (0);
}
