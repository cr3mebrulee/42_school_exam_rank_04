#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

#define DEBUG

int create_pipes(int fds[][2], int n)
{
    for (int i = 0; i < n - 1; i++)
	{
        if (pipe(fds[i]) == -1)
		{
            return (-1);
        }
    }
    return (0);
}

// Function to handle the redirection and file descriptor management for each child
int handle_redirection(int i, int n, int fds[][2]) 
{
    // First command: redirect stdout to the first pipe
    if (i == 0)
	{
        dup2(fds[i][1], STDOUT_FILENO);
        close(fds[i][1]);
    }
    // Intermediate commands: redirect stdin and stdout to pipes
    else if (i > 0 && i < n - 1)
	{
        dup2(fds[i - 1][0], STDIN_FILENO);  // Read from previous pipe
        close(fds[i - 1][0]);
        dup2(fds[i][1], STDOUT_FILENO);     // Write to current pipe
        close(fds[i][1]);
    }
    // Last command: redirect stdin from the previous pipe
    else if (i == n - 1)
	{
        dup2(fds[i - 1][0], STDIN_FILENO);  // Read from previous pipe
        close(fds[i - 1][0]);
    }
    // Close all pipe fds
    for (int j = 0; j < n - 1; j++)
	{
        close(fds[j][0]);
        close(fds[j][1]);
    }
    return (0);
}

// Function to fork the child process and execute the command
int execute_command(char **cmds[], int i, int n, int fds[][2]) 
{
    pid_t cpid = fork();
    if (cpid == 0) 
	{
        // Handle redirection
        if (handle_redirection(i, n, fds) == -1) 
		{
            return (-1);
        }
        // Execute command
        if (execvp(cmds[i][0], cmds[i]) == -1) 
		{
            return (-1);
        }
    }
    return (0);
}

// Main function that sets up the pipe execution
int execute_in_pipe(char **cmds[], int n) 
{
    int fds[n - 1][2];
    pid_t cpid;

    // Create pipes
    if (create_pipes(fds, n) == -1) 
	{
        return (-1);
    }
    // Execute commands
    for (int i = 0; i < n; i++) 
	{
        if (execute_command(cmds, i, n, fds) == -1) 
		{
            return (-1);
        }
    }
    // Parent process: close pipe fds and wait for children
    for (int i = 0; i < n - 1; i++)
	{
        close(fds[i][0]);
        close(fds[i][1]);
    }
    for (int i = 0; i < n; i++) 
	{
        wait(NULL);  // Wait for all children
    }
    return (0);
}

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

int	picoshell(char **cmds[])
{
	int		n;

	if (calculate_cmds(cmds, &n) == -1)
		return (1);
	#ifdef DEBUG
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
