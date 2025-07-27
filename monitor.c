#include "philo.h"

int philo_died(t_philo *philo)
{
	safe_mutex(pthread_mutex_lock(philo->meal_lock), LOCK);
	if (get_time_mc() - philo->last_meal_time >=
			philo->data->time_to_die && !philo->is_eating)
	{
		safe_mutex(pthread_mutex_unlock(philo->meal_lock), UNLOCK);
		return (1);
	}
	safe_mutex(pthread_mutex_unlock(philo->meal_lock), UNLOCK);
	return (0);
}

int if_all_eaten(t_philo *philo)
{
	int i;
	int finished_eating;

	i = 0;
	finished_eating = 0;
	if (philo->data->meal_max_limit < 0)
		return (0); 
	if (safe_mutex(pthread_mutex_lock(philo[i].meal_lock), LOCK) == -1)
		return (-1);
	while (i < philo->data->philo_nbr)
	{		
		if (philo[i].meal_counter >= philo[i].data->meal_max_limit)
			finished_eating++;
		i++;
	}
	if (safe_mutex(pthread_mutex_unlock(philo->meal_lock), UNLOCK) == -1)
		return (-1);
	if (finished_eating == philo->data->philo_nbr)
	{
		if (safe_mutex(pthread_mutex_lock(philo->dead_lock), LOCK) == -1)
			return (-1);
		philo->data->end_flag = 1;
		if (safe_mutex(pthread_mutex_unlock(philo->dead_lock), UNLOCK) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

void *monitor(void *arg)
{
	t_data *data;
	int i;

	data = (t_data *)arg;
	while (!data->end_flag)
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			if (philo_died(&data->philo[i]))
			{
				if (safe_mutex(pthread_mutex_lock(&data->dead_lock), LOCK) == -1 || safe_mutex(pthread_mutex_lock(&data->write_lock), LOCK) == -1)
					return (NULL);
				print_msg(&data->philo[i], DIED);
				data->end_flag = 1;
				if (safe_mutex(pthread_mutex_unlock(&data->dead_lock), UNLOCK) == -1 || safe_mutex(pthread_mutex_unlock(&data->write_lock), UNLOCK) == -1)
					return (NULL);
				return (NULL);
			}
			i++;
		}
		if (data->meal_max_limit > 0 && if_all_eaten(data->philo) == 1)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}