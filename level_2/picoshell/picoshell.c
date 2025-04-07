#include <sys/types.h>
#include <unistd.h>

int execvp(const char *file, char *const argv[]);
int dup2(int oldfd, int newfd);

int ft_strncmpt(char *s1, char *s2, int n)
{
	while (*s1 && *s2 && n > 0)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		n--;
		s1++;
		s2++;
	}
	if (n > 0)
		return (*s1 - *s2);
	return (0);
}

int	calculate_cmds(char **cmds[], int *n)
{
	int	i = 0;
	int	j = 0;

	if (!cmds || ! *cmds[0] || !cmds[0][0])
		return (-1);
	while (cmds[i][j] != NULL)
	{
		if (ft_strncpm(cmds[i][j], "|", 1) == 0)
			*(n++);
		i++;
	}
}

int	picoshell(char **cmds[])
{
	int		n;
	int		num;
	int		pipefds[2 * (num - 1)];
	pid_t	cpid;

	if (calculate_cmds(cmds, &n) == -1)
		return (1);
	num = n;
	if (num >= 1)
	{
		while (**cmds[num])
		{

		}
	}
	else
		if (execvp(*cmds[0], cmds[0]) == -1)
			return (1);
	//close fds
	return (0);
}
