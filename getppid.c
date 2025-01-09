#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "shell.h"

/**
 * print_getppid - Entry point of the program.
 *
 * Description: This function retrieves and prints the PID of
 * the parent process
 * using the `getppid()` system call.
 *
 * Return: Always 0 (Success).
 */
int print_getppid(void)
{
	pid_t parent_pid = getppid();

	printf("PID du processus parent : %d\n", parent_pid);

	return (0);
}
