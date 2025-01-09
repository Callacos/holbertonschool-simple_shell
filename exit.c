#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "shell.h"

/**
 * custom_exit - Exits the shell with a custom status
 * @args: The arguments passed to the exit command
 */

void custom_exit(char *args)
{
(void)args;
free(args);
exit(0);
}

