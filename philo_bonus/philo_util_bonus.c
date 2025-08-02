#include "philo_bonus.h"

long long	get_time_mc(void)
{
	struct timeval	tv;
	long long		timestamp;

	if (gettimeofday(&tv, NULL))
		error_exit("Failed calling gettimeofday()");
	timestamp = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
	return (timestamp);
}

void	philo_usleep(t_data *data, long time_ms)
{
	long	start;

	start = get_time_mc();
	while (get_time_mc() - start < time_ms)
	{
		usleep(200);
		safe_mutex(pthread_mutex_lock(&data->dead_lock), LOCK);
		if (data->end_flag)
		{
			safe_mutex(pthread_mutex_unlock(&data->dead_lock), UNLOCK);
			break ;
		}
		safe_mutex(pthread_mutex_unlock(&data->dead_lock), UNLOCK);
	}
}
