#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	sandbox(void (*f)(void), unsigned int timeout, int verbose);

/* Nice function */
void	nice_function(void)
{
	printf("Hello from nice_function!\n");
}

/* Causes segmentation fault */
void	segfault_function(void)
{
	int	*ptr = NULL;
	*ptr = 42;
}

/* Runs forever */
void	infinite_loop(void)
{
	while (1) {}
}

/* Exits with error code 42 */
void	exit_with_error(void)
{
	exit(42);
}

int	main()
{
	sandbox(nice_function, 2, 1);
	sandbox(exit_with_error, 2, 1);
	sandbox(segfault_function, 2, 1);
	sandbox(infinite_loop, 2, 1);
	return (0);
}
