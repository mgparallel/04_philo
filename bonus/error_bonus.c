#include "philo_bonus.h"

void	error_exit(char *msg)
{
	printf("%s\n", msg);
	exit (EXIT_FAILURE);
}

void	*safe_malloc(size_t size)
{
	void	*struc;

	struc = malloc(size);
	if (!struc)
		error_exit("Failed malloc");
	return (struc);
}