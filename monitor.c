#include "philo.h"

int	philo_died(t_philo *philo)
{
	int		result;
	long	current_time;

	result = 0;
	current_time = get_time_mc();
	safe_mutex(pthread_mutex_lock(&philo->data->meal_lock), LOCK);
	// if (current_time >= philo->data->start_time)
	// {
	if (current_time - philo->last_meal_time >= philo->data->time_to_die
		&& !philo->is_eating)
		result = 1;
	// }
	safe_mutex(pthread_mutex_unlock(&philo->data->meal_lock), UNLOCK);
	return (result);
}

int	if_all_eaten(t_philo *philo)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philo->data->meal_max_limit <= 0)
		return (0);
	if (safe_mutex(pthread_mutex_lock(&philo->data->meal_lock), LOCK) == -1)
		return (-1);
	while (i < philo->data->philo_nbr)
	{
		if (philo[i].meal_counter >= philo[i].data->meal_max_limit)
			finished_eating++;
		i++;
	}
	if (safe_mutex(pthread_mutex_unlock(&philo->data->meal_lock), UNLOCK) == -1)
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

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (get_time_mc() < data->start_time)
		usleep(1000);
	while (1)
	{
		safe_mutex(pthread_mutex_lock(&data->dead_lock), LOCK);
		if (data->end_flag)
		{
			safe_mutex(pthread_mutex_unlock(&data->dead_lock), UNLOCK);
			break ;
		}
		safe_mutex(pthread_mutex_unlock(&data->dead_lock), UNLOCK);
		i = 0;
		while (i < data->philo_nbr)
		{
			if (philo_died(&data->philo[i]))
			{
				safe_mutex(pthread_mutex_lock(&data->dead_lock), LOCK);
				if (!data->end_flag)
				{
					safe_mutex(pthread_mutex_lock(&data->write_lock), LOCK);
					print_msg(&data->philo[i], DIED);
					safe_mutex(pthread_mutex_unlock(&data->write_lock), UNLOCK);
					data->end_flag = 1;
				}
				safe_mutex(pthread_mutex_unlock(&data->dead_lock), UNLOCK);
				return (NULL);
			}
			i++;
		}
		if (data->meal_max_limit > 0 && if_all_eaten(data->philo) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
