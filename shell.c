#include "shell.h"
/**
 * main - main entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *cmd = NULL;
	size_t len = 0;
	char *stkn;
	pid_t my_pid;
	int status;
	ssize_t nread = 0;

	while (1)
	{
		printf("#cisfun$ ");
		nread = getline(&cmd, &len, stdin);
		if (nread == EOF)
		{
			printf("\n");
			return (nread);
		}
		stkn = strtok(cmd, " \n");
		argv = malloc(sizeof(char *) * 32);
		argv[0] = stkn;
		argc = 1;
		while (stkn != NULL)
		{
			stkn = strtok(NULL, " \n");
			argv[argc] = stkn;
			argc++;
		}
		my_pid = fork();
		if (my_pid == -1)
		{
			perror("Error:");
			return (1);
		}
		if (my_pid == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror(argv[0]);
				return (1);
			}
			execve(argv[0], argv, NULL);
		}
		wait(&status);
	}
	free(cmd);
	return (0);
}
