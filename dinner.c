#include "philo.h"

void	think_mode(t_philo *philo)
{
	print_msg(philo, THINK);
}

void	sleep_mode(t_philo *philo)
{
	print_msg(philo, SLEEP);
	philo_usleep(philo->data->time_to_sleep);
}

void	eat_mode(t_philo *philo)
{
	safe_mutex(pthread_mutex_lock(philo->first_fork), LOCK);
	print_msg(philo, FORK);
	safe_mutex(pthread_mutex_lock(&philo->data->dead_lock), LOCK);
	if (philo->data->end_flag)
	{
		safe_mutex(pthread_mutex_unlock(&philo->data->dead_lock), UNLOCK);
		safe_mutex(pthread_mutex_unlock(philo->first_fork), UNLOCK);
		return ;
	}
	safe_mutex(pthread_mutex_unlock(&philo->data->dead_lock), UNLOCK);
	safe_mutex(pthread_mutex_lock(philo->second_fork), LOCK);
	print_msg(philo, FORK);
	safe_mutex(pthread_mutex_lock(&philo->data->meal_lock), LOCK);
	philo->is_eating = true;
	philo->last_meal_time = get_time_mc();
	philo->meal_counter++;
	safe_mutex(pthread_mutex_unlock(&philo->data->meal_lock), UNLOCK);
	print_msg(philo, EAT);
	philo_usleep(philo->data->time_to_eat);
	safe_mutex(pthread_mutex_lock(&philo->data->meal_lock), LOCK);
	philo->is_eating = false;
	if (philo->data->meal_max_limit > 0
		&& philo->meal_counter >= philo->data->meal_max_limit)
		philo->is_full = true;
	safe_mutex(pthread_mutex_unlock(&philo->data->meal_lock), UNLOCK);
	safe_mutex(pthread_mutex_unlock(philo->first_fork), UNLOCK);
	safe_mutex(pthread_mutex_unlock(philo->second_fork), UNLOCK);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		philo_usleep(50);
	while (get_time_mc() < philo->data->start_time)
		philo_usleep(1);
	while (1)
	{
		safe_mutex(pthread_mutex_lock(&philo->data->dead_lock), LOCK);
		if (philo->data->end_flag)
		{
			safe_mutex(pthread_mutex_unlock(&philo->data->dead_lock), UNLOCK);
			break ;
		}
		safe_mutex(pthread_mutex_unlock(&philo->data->dead_lock), UNLOCK);
		// Check if philosopher is full
		safe_mutex(pthread_mutex_lock(&philo->data->meal_lock), LOCK);
		if (philo->is_full)
		{
			safe_mutex(pthread_mutex_unlock(&philo->data->meal_lock), UNLOCK);
			philo_usleep(10);
			continue ;
		}
		safe_mutex(pthread_mutex_unlock(&philo->data->meal_lock), UNLOCK);
		if (philo->data->end_flag)
			break ;
		eat_mode(philo);
		if (philo->data->end_flag)
			break ;
		sleep_mode(philo);
		if (philo->data->end_flag)
			break ;
		think_mode(philo);
	}
	return (arg);
}

int	single_philo(t_data *data)
{
	data->start_time = get_time_mc();
	safe_mutex(pthread_mutex_lock(data->philo->first_fork), LOCK);
	print_msg(data->philo, FORK);
	philo_usleep(data->time_to_die);
	safe_mutex(pthread_mutex_unlock(data->philo->first_fork), UNLOCK);
	print_msg(data->philo, DIED);
	return (1);
}

int	dinner_start(t_data *data)
{
	int			i;
	pthread_t	check;

	if (data->philo_nbr == 1)
		return (single_philo(data));
	data->start_time = get_time_mc() + 100;
	i = 0;
	while (i < data->philo_nbr)
	{
		safe_mutex(pthread_mutex_lock(&data->meal_lock), LOCK);
		data->philo[i].last_meal_time = data->start_time;
		safe_mutex(pthread_mutex_unlock(&data->meal_lock), UNLOCK);
		i++;
	}
	i = 0;
	while (i < data->philo_nbr)
	{
		if (safe_thread_handle(&data->philo[i].thread_id, &routine,
				&data->philo[i], CREATE) == -1)
			return (-1);
		i++;
	}
	// delay to ensure all philosopher threads are ready
	philo_usleep(10);
	// monitor thread
	if (safe_thread_handle(&check, monitor, data, CREATE) == -1)
		return (-1);
	safe_thread_handle(&check, NULL, NULL, JOIN);
	// Signal all threads to end
	safe_mutex(pthread_mutex_lock(&data->dead_lock), LOCK);
	data->end_flag = 1;
	safe_mutex(pthread_mutex_unlock(&data->dead_lock), UNLOCK);
	// Join all philosopher threads
	i = 0;
	while (i < data->philo_nbr)
	{
		safe_thread_handle(&data->philo[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	return (0);
}
