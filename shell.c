#include "shell.h"

/**
 * main - main entry point
 *
 * Return: Always 0
 */

int main(void)
{
	char *buffer = NULL;
	size_t len = 0;
	char *stkn;
	pid_t my_pid;
	int status;
	ssize_t read = 0;

	while (1)
	{
		printf("#cisfun$ ");
		read = getline(&buffer, &len, stdin); /*Get input from user*/
		if (read == EOF)
		{
			printf("\n");
			return (read);
		}
		stkn = strtok(buffer, "\n");
		char *arr[] = {stkn, NULL};

		my_pid = fork();
		if (my_pid == -1)
		{
			perror("Error:");
			return (1);
		}
		else if (my_pid == 0)
		{
			if (execve(arr[0], arr, NULL) == -1)
			{
				perror(arr[0]);
				return (1);
			}
			execve(arr[0], arr, NULL);
		}
		else
			wait(&status);

	}
	free(buffer);
	return (0);
}
