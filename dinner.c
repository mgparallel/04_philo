#include "philo.h"

void think_mode(t_philo *philo)
{
	print_msg(philo, THINK);
}

void sleep_mode(t_philo *philo)
{
	print_msg(philo, SLEEP);
	philo_usleep(philo->data->time_to_sleep);
}

void eat_mode(t_philo *philo)
{
	safe_mutex(pthread_mutex_lock(philo->first_fork), LOCK);
	print_msg(philo, FORK);
	safe_mutex(pthread_mutex_lock(philo->second_fork), LOCK);
	print_msg(philo, FORK);
	print_msg(philo, EAT);
	safe_mutex(pthread_mutex_lock(philo->meal_lock), LOCK);
	philo->is_eating = true;
	philo->last_meal_time = get_time_mc();
	philo->meal_counter++;
	safe_mutex(pthread_mutex_unlock(philo->meal_lock), UNLOCK);
	philo_usleep(philo->data->time_to_eat);
	safe_mutex(pthread_mutex_lock(philo->meal_lock), LOCK);
	philo->is_eating = false;
	if (philo->data->meal_max_limit > 0 &&
		philo->meal_counter == philo->data->meal_max_limit)
		philo->is_full = true;
	safe_mutex(pthread_mutex_unlock(philo->meal_lock), UNLOCK);
	safe_mutex(pthread_mutex_unlock(philo->first_fork), UNLOCK);
	safe_mutex(pthread_mutex_unlock(philo->second_fork), UNLOCK);
}

void *routine(void *arg) 
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		philo_usleep(10);
	while (get_time_mc() < philo->data->start_time)
		philo_usleep(1);
	while (!(philo->data->end_flag))
	{
		if (philo->is_full)
		{
			philo_usleep(10);
			continue ;
		}
		eat_mode(philo);
		sleep_mode(philo);
		think_mode(philo);
	}
	return (arg);
}

int single_philo(t_data *data)
{
	print_msg(data->philo, FORK);
	philo_usleep(data->time_to_die);
	print_msg(data->philo, DIED);
	return (1);
}

int dinner_start(t_data *data)
{
	int i;
	pthread_t check;

	i = 0;
	// if (data->meal_max_limit < 0)
	// 	return (-1);
	if (data->philo_nbr == 1)
		return (single_philo(data));
	data->start_time = get_time_mc();
	if (safe_thread_handle(&check, monitor, data->philo, CREATE) == -1)
		return (-1);
	while (i < data->philo_nbr)
	{
		if (safe_thread_handle(&data->philo[i].thread_id, &routine, &data->philo[i], CREATE) == -1)
			return (-1);
		i++;
	}
	safe_thread_handle(&check, NULL, NULL, JOIN);
	safe_mutex(pthread_mutex_lock(&data->dead_lock), LOCK);
	data->end_flag = 1;
	safe_mutex(pthread_mutex_unlock(&data->dead_lock), UNLOCK);
	i = 0;
	while (i < data->philo_nbr)
	{
		safe_thread_handle(&data->philo[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	return (0);
}