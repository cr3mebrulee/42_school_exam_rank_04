#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

static volatile	sig_atomic_t timeout_flag = 0;

// Signal handler for SIGALRM
void	handle_alarm(int sig)
{
	(void)sig; // Ignore unused parameter warning
	timeout_flag = 1; // Set the timeout flag when SIGALRM is received
}

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t				cpid;
	struct sigaction 	sa;
	int					status;
	pid_t				ret;

	sa.sa_handler = handle_alarm;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGALRM, &sa, NULL) == -1)
	{
		perror("sigaction failed");
		return (-1);
	}
	cpid = fork();
	if (cpid == -1)
		exit (-1);
	if (cpid == 0)
	{
		f();
		exit (0);
	}
	else
	{
		alarm (timeout); // Starts a timer

		ret = waitpid(cpid, &status, 0);
		if (timeout_flag)
		{
			kill(cpid, SIGKILL); // Ensure child is terminated
			if (verbose)
				printf("Bad function: timed out after %u seconds\n", timeout);
			return (0);
		}
		if (ret == 0 && WIFEXITED(status)) // Check if the child terminated normally
		{
			if (WEXITSTATUS(status) == 0) // Check the exit status of the child
			{
				if (verbose)
					printf("Nice function!\n");
				return (1);
			}
		}
		else if (WIFSIGNALED(status)) // Checks if the child process was terminated by a signal
		{
			if (verbose)
				printf("Bad function: %s\n", strsignal(WTERMSIG(status)));
			return (0);
		}
	}
	return (-1);
}
