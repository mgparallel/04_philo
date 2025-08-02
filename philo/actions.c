/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:38:56 by menwu             #+#    #+#             */
/*   Updated: 2025/07/31 22:41:18 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think_mode(t_philo *philo)
{
	print_msg(philo, THINK);
}

void	sleep_mode(t_philo *philo)
{
	print_msg(philo, SLEEP);
	philo_usleep(philo->data, philo->data->time_to_sleep);
}

void	update_full(t_philo *philo)
{
	safe_mutex(pthread_mutex_lock(&philo->data->meal_lock), LOCK);
	philo->is_eating = false;
	if (philo->data->meal_max_limit > 0
		&& philo->meal_counter >= philo->data->meal_max_limit)
		philo->is_full = true;
	safe_mutex(pthread_mutex_unlock(&philo->data->meal_lock), UNLOCK);
}

void	eat_mode(t_philo *philo)
{
	safe_mutex(pthread_mutex_lock(philo->first_fork), LOCK);
	safe_mutex(pthread_mutex_lock(&philo->data->meal_lock), LOCK);
	philo->last_meal_time = get_time_mc();
	safe_mutex(pthread_mutex_unlock(&philo->data->meal_lock), UNLOCK);
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
	philo->meal_counter++;
	safe_mutex(pthread_mutex_unlock(&philo->data->meal_lock), UNLOCK);
	print_msg(philo, EAT);
	philo_usleep(philo->data, philo->data->time_to_eat);
	update_full(philo);
	safe_mutex(pthread_mutex_unlock(philo->first_fork), UNLOCK);
	safe_mutex(pthread_mutex_unlock(philo->second_fork), UNLOCK);
}
