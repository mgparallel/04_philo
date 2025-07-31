/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:28:00 by menwu             #+#    #+#             */
/*   Updated: 2025/07/31 22:28:01 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_philo *philo)
{
	long	current_time;
	long	time_since_last_meal;

	current_time = get_time_mc();
	safe_mutex(pthread_mutex_lock(&philo->data->meal_lock), LOCK);
	time_since_last_meal = current_time - philo->last_meal_time;
	safe_mutex(pthread_mutex_unlock(&philo->data->meal_lock), UNLOCK);
	if (time_since_last_meal > philo->data->time_to_die)
		return (1);
	return (0);
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
		return (1);
	return (0);
}

int	loop_philo_died(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (philo_died(&data->philo[i]))
		{
			safe_mutex(pthread_mutex_lock(&data->dead_lock), LOCK);
			if (!data->end_flag)
				data->end_flag = 1;
			safe_mutex(pthread_mutex_unlock(&data->dead_lock), UNLOCK);
			print_msg(&data->philo[i], DIED);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*detect_all_full(t_data *data)
{
	safe_mutex(pthread_mutex_lock(&data->dead_lock), LOCK);
	if (!data->end_flag)
		data->end_flag = 1;
	safe_mutex(pthread_mutex_unlock(&data->dead_lock), UNLOCK);
	return (NULL);
}

void	*monitor(void *arg)
{
	t_data	*data;

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
		if (loop_philo_died(data))
			return (NULL);
		if (data->meal_max_limit > 0 && if_all_eaten(data->philo) == 1)
			return (detect_all_full(data));
		usleep(5000);
	}
	return (NULL);
}
