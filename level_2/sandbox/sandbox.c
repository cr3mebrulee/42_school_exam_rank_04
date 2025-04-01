#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

static volatile sig_atomic_t timeout_flag = 0;

// Signal handler for SIGALRM
void	handle_alarm(int sig)
{
	(void)sig;
	timeout_flag = 1;
}

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t				cpid;
	struct sigaction 	sa;
	int					status;
	pid_t				ret;

	// Setup signal handling for timeout
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
	{
		perror("fork failed");
		return (-1);
	}

	if (cpid == 0) // Child process
	{
		// Reset signals to default to avoid inheriting parent's handlers
		struct sigaction sa_default = { .sa_handler = SIG_DFL };
		sigaction(SIGALRM, &sa_default, NULL);

		f(); // Execute function
		exit(0);
	}
	else // Parent process
	{
		alarm(timeout); // Start timeout
		// Check if child finishes before timeout
		while (1)
		{
			ret = waitpid(cpid, &status, WNOHANG);
			if (ret == cpid) // Child exited
			{
				if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
				{
					if (verbose)
						printf("Nice function!\n");
					return (1);
				}
				else if (WIFSIGNALED(status))
				{
					if (verbose)
						printf("Bad function: %s\n", strsignal(WTERMSIG(status)));
					return (0);
				}
				else
					return (0);
			}
			else if (timeout_flag) // Timeout occurred
			{
				kill(cpid, SIGKILL); // Kill child process
				waitpid(cpid, &status, 0); // Clean up zombie process
				if (verbose)
					printf("Bad function: timed out after %u seconds\n", timeout);
				return (0);
			}
			usleep(1000); // Sleep briefly to reduce CPU usage
		}
	}
}
