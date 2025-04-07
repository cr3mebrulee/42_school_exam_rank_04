#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

#define DEBUG

int	calculate_cmds(char **cmds[], int *n)
{
	int	i = 0;

	if (!cmds || ! *cmds[0] || !cmds[0][0])
		return (-1);
	while (cmds[i] != NULL)
	{
		i++;
	}
	*n = i;
	return (0);
}

int execute_in_pipe(char **cmds[], int n)
{
	int		fds[n -1][2];
	pid_t	cpid;

	//create all pipes
	for (int i = 0; i < n - 1; i++)
	{
		if (pipe(fds[i]) == -1)
			return (-1);
	}
	for (int i = 0; i < n; i++) 
	{
		cpid = fork();
		if (cpid == 0) 
		{
			// First command: redirect stdout to the first pipe
			if (i == 0) 
			{
				dup2(fds[i][1], STDOUT_FILENO);
			}
			// Intermediate commands: redirect stdin and stdout to pipes
			else if (i > 0 && i < n - 1) 
			{
				dup2(fds[i - 1][0], STDIN_FILENO);  // Read from previous pipe
				dup2(fds[i][1], STDOUT_FILENO);     // Write to current pipe
			}
			// Last command: redirect stdin from the previous pipe
			else if (i == n - 1) 
			{
				dup2(fds[i - 1][0], STDIN_FILENO);  // Read from previous pipe
			}
			// Close all pipe fds
			for (int j = 0; j < n - 1; j++) 
			{
				close(fds[j][0]);
				close(fds[j][1]);
			}
			// Execute command
			if (execvp(cmds[i][0], cmds[i]) == -1)
				return (-1);
		}
	}
	// Parent process: close pipe fds and wait for children
	for (int i = 0; i < n - 1; i++) {
	    close(fds[i][0]);
	    close(fds[i][1]);
	}
	for (int i = 0; i < n; i++) {
	    wait(NULL);  // Wait for all children
	}
	return (0);
}

int	picoshell(char **cmds[])
{
	int		n;

	if (calculate_cmds(cmds, &n) == -1)
		return (1);
	#ifdef debug
		printf("Commands number %d\n", n);
	#endif
	if (n == 1)
	{
		if (execvp(cmds[0][0], cmds[0]) == -1)
			return (1);
		return (0);
	}
	else
		if (execute_in_pipe(cmds, n) == -1)
			return (1);
	return (0);
}
