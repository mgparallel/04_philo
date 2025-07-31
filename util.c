#include "philo.h"

long long	get_time_mc(void)
{
	struct timeval	tv;
	long long		timestamp;

	if (gettimeofday(&tv, NULL))
		error_exit("Failed calling gettimeofday()");
	timestamp = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
	return (timestamp);
}

// void destroy(t_data *data, t_mtx *fork)
// {
// 	int i;

// 	i = 0;
// 	pthread_mutex_destroy(&data->write_lock);
// 	pthread_mutex_destroy(&data->dead_lock);
// 	pthread_mutex_destroy(&data->meal_lock);
// 	while (i < data->philo_nbr)
// 	{
// 		pthread_mutex_destroy(&fork[i]);
// 		i++;
// 	}
// }

// void philo_usleep(long time_ms)
// {
// 	long start;

// 	start = get_time_mc();
// 	while (get_time_mc() - start < time_ms)
// 		usleep(100);
// }