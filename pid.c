#include <stdio.h>
#include <unistd.h>
#include <sched.h>

/**
 * pid - PID
 *
 * Return: Always 0.
 */
int pid(void)
{
pid_t my_pid;

my_pid = getpid();
printf("%u\n", my_pid);
return (0);
}
