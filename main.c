#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "shell.h"

/**
 * main - shell loop
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: nothing
 */

int main(int argc, char *argv[])
{
	char *inpu = NULL;
	size_t bufsiz = 0;
	char *comands[MAXI_COMMANDS];
	char **comand_args;
	int i;
	int numer_commands, from_pippe = 0;
	(void)argc;

	while (1 && !from_pippe)
	{
		if (isatty(STDIN_FILENO) == 0)
			from_pippe = 1;
		read_inpu(&inpu, &bufsiz);
		perse_inpu(inpu, comands, &numer_commands);
		if (numer_commands > 0)
		{
			if (strcmp(comands[0], "exit") == 0)
			{
				free(inpu);
				exit(EXIT_SUCCESS);
			}
			comand_args = get_comand(inpu);
			execute_comand(comands[0], comands, argv[0]);
			for (i = 0; comand_args[i] != NULL; i++)
			{
				free(comand_args[i]);
			}
			free(comand_args);
		}
		free(inpu);
		inpu = NULL;
	}
	return (0);
}
