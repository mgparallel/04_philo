/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:38:20 by menwu             #+#    #+#             */
/*   Updated: 2025/07/31 22:44:02 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (philo->data->end_flag == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		philo_usleep(philo->data, 100);
	while (get_time_mc() < philo->data->start_time)
		philo_usleep(philo->data, 1);
	while (!dead_loop(philo))
	{
		eat_mode(philo);
		if (dead_loop(philo))
			break ;
		sleep_mode(philo);
		if (dead_loop(philo))
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
	philo_usleep(data, data->time_to_die);
	safe_mutex(pthread_mutex_unlock(data->philo->first_fork), UNLOCK);
	print_msg(data->philo, DIED);
	return (1);
}

int	monitor_thread(pthread_t *check, t_data *data)
{
	int	i;

	philo_usleep(data, 10);
	if (safe_thread_handle(check, monitor, data, CREATE) == -1)
		return (-1);
	safe_thread_handle(check, NULL, NULL, JOIN);
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
	if (monitor_thread(&check, data) == -1)
		return (-1);
	return (0);
}
