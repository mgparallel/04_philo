/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:56:42 by menwu             #+#    #+#             */
/*   Updated: 2025/07/31 22:43:20 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_msg_util(t_philo *philo)
{
	safe_mutex(pthread_mutex_lock(&philo->data->dead_lock), LOCK);
	if (philo->data->end_flag)
	{
		safe_mutex(pthread_mutex_unlock(&philo->data->dead_lock), UNLOCK);
		return (1);
	}
	safe_mutex(pthread_mutex_unlock(&philo->data->dead_lock), UNLOCK);
	return (0);
}

void	print_msg(t_philo *philo, t_mode mode)
{
	long	time;

	if (mode != DIED)
	{
		if (print_msg_util(philo))
			return ;
	}
	safe_mutex(pthread_mutex_lock(philo->write_lock), LOCK);
	time = get_time_mc() - philo->data->start_time;
	if (mode == EAT)
		printf("%ld %d is eating\n", time, philo->id);
	else if (mode == FORK)
		printf("%ld %d has taken a fork\n", time, philo->id);
	else if (mode == SLEEP)
		printf("%ld %d is sleeping\n", time, philo->id);
	else if (mode == THINK)
		printf("%ld %d is thinking\n", time, philo->id);
	else if (mode == DIED)
		printf("%ld %d died\n", time, philo->id);
	else
		printf("Incorrect message type\n");
	safe_mutex(pthread_mutex_unlock(philo->write_lock), UNLOCK);
}

int	main(int ac, char **ag)
{
	t_data	*data;

	if (ac != 5 && ac != 6)
		return (error_exit("Incorrect number of arguments"));
	data = safe_malloc(sizeof(t_data));
	if (parse_input(data, ag) == -1)
		return (1);
	data_init(data);
	dinner_start(data);
	destroy(data, data->fork);
	return (0);
}
