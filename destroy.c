#include "philo.h"

void	destroy(t_data *data, t_mtx *fork)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	while (i < data->philo_nbr)
	{
		pthread_mutex_destroy(&fork[i]);
		i++;
	}
}