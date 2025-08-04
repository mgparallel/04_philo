#include "philo_bonus.h"

int	count_size(long n)
{
	int	size;

	size = 0;
	if (n < 0)
		n *= -1;
	if (n == 0)
		size = 1;
	while (n > 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*recursion(long n, char *result, int i)
{
	if (n < 0)
	{
		result[0] = '-';
		n *= -1;
	}
	if (n == 0)
		result[i - 1] = '0';
	else
	{
		result[i - 1] = n % 10 + '0';
		i--;
		if (n / 10 != 0)
		{
			n = n / 10;
			recursion(n, result, i);
		}
	}
	return (result);
}

char	*ft_itoa(long n)
{
	char	*result;
	int		size;
	long	new;

	new = (long)n;
	size = count_size(new);
	if (new < 0)
		size += 1;
	result = (char *)malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	recursion(new, result, size);
	result[size] = '\0';
	return (result);
}

long long	get_time_mc(void)
{
	struct timeval	tv;
	long long		timestamp;

	if (gettimeofday(&tv, NULL))
		error_exit("Failed calling gettimeofday()");
	timestamp = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
	return (timestamp);
}

void	philo_usleep(t_core *core, long time_ms)
{
	long	start;

	start = get_time_mc();
	while (get_time_mc() - start < time_ms)
	{
		usleep(200);
		// safe_mutex(pthread_mutex_lock(&data->dead_lock), LOCK);
		// if (core->sems)
		// {
		// 	safe_mutex(pthread_mutex_unlock(&data->dead_lock), UNLOCK);
		// 	break ;
		// }
		// safe_mutex(pthread_mutex_unlock(&data->dead_lock), UNLOCK);
	}
}

void	destroy(t_core *core, int parent_prc)
{
	int	i;

	i = 0;
	if (parent_prc)
	{
		while (i < core->philo_nbr)
		{
			if (core->pids[i] != -1)
				kill(core->pids[i], SIGTERM);
			i++;
		}
	}
	i = 0;
	while (i < core->philo_nbr)
	{
		if (core->pids[i] != -1)
			waitpid(core->pids[i], NULL, 0);
		i++;
	}
	free(core->pids);
	//here continue!
	if (core->sems->die_sem)

	
	free(data);
	free(data->philo);
}
