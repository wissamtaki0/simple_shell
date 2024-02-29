#ifndef _SHELL_H
#define _SHELL_H

#define MAXI_COMMANDS 100

void read_inpu(char **bufer, size_t *n);
void perse_inpu(char *inpu, char **comands, int *numer_comands);
void execute_comand(char *comand, char **argumentss, char *argv);
char **get_comand(char *inpu);

#endif /* _SHELL_H */
