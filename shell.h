#ifndef SHELL_H
#define SHELL_H

extern char **environ;
void custom_exit(char **args);
int print_env(char **env);
char *locate_executable(char *command, char *path);


#endif
