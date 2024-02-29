#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stddef.h>
#include "shell.h"
/**
 * read_inpu - reads the input from the command line
 * @bufer: the buffer where to store the user input
 * @n: pointer to the buffer size
 *
 * Return: nothing
 */

void read_inpu(char **bufer, size_t *n)
{
	char *promptt = " ($) ";
	ssize_t bytesReadd;

	if (bufer == NULL || n == NULL)
		return;

	if (isatty(STDIN_FILENO) == 1)
		write(STDOUT_FILENO, promptt, 5);

	bytesReadd = getline(bufer, n, stdin);

	if (bytesReadd == -1)
	{
		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("(getline)");
			exit(EXIT_FAILURE);
		}
	}

	if ((*bufer)[bytesReadd - 1] == '\n')
		(*bufer)[bytesReadd - 1] = '\0';
}


/**
 * perse_inpu - separate the input string to tokens
 * @inpu: the input from the command line
 * @comands: a table of strings where cammands will be stored
 * @numer_commands: the size of the commands array
 *
 * Return: nothing
 */

void perse_inpu(char *inpu, char **comands, int *numer_commands)
{
	char *tokenn;
	int countt = 0;

	tokenn = strtok(inpu, " \t\n");
	while (tokenn != NULL)
	{
		comands[countt] = tokenn;
		tokenn = strtok(NULL, " \t\n");
		countt++;
	}
	comands[countt] = NULL;
	*numer_commands = countt;
}
/**
 * execute_comand - execute command passed to the function
 * @comand: the command to be executed
 * @argumentss: the arguments of the command
 * @argv: my executable name
 *
 * Return: nothing
 */

void execute_comand(char *comand, char **argumentss, char *argv)
{
	int statuss;
	char *pathh;
	char *path_copyy;
	char *tokenn;
	char command_pathh[100];
	pid_t pidd = fork();

	if (pidd == -1)
	{
		perror(argv);
		exit(EXIT_FAILURE);
	}
	else if (pidd == 0)
	{
		if (strchr(comand, '/') != NULL)
			execvp(comand, argumentss);
		else
		{
			pathh = getenv("PATH");
			path_copyy = strdup(pathh);
			tokenn = strtok(path_copyy, ":");

			while (tokenn != NULL)
			{
				snprintf(command_pathh, sizeof(command_pathh), "%s/%s", tokenn, comand);
				execvp(command_pathh, argumentss);
				tokenn = strtok(NULL, ":");
			}
			free(path_copyy);
		}
		fprintf(stderr, "%s: command not found\n", argv);
		/*
		 * perror(command);
		 */
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pidd, &statuss, 0);
	}
}

/**
 * get_comand - retrieves the command and arguments from the input
 * @inpu: the input from the command line
 *
 * Return: an array of strings with the command and arguments
 */
char **get_comand(char *inpu)
{
	int i;
	char *tokenn;
	char **comand_args = malloc((MAXI_COMMANDS + 1) * sizeof(char *));

	if (comand_args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	i = 0;
	tokenn = strtok(inpu, " \t\n");

	while (tokenn != NULL && i < MAXI_COMMANDS)
	{
		comand_args[i] = strdup(tokenn);
		tokenn = strtok(NULL, " \t\n");
		i++;
	}
	comand_args[i] = NULL;

	return (comand_args);
}
