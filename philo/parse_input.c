/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:33:18 by menwu             #+#    #+#             */
/*   Updated: 2025/08/03 00:36:23 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_space(char ch)
{
	return ((ch >= 9 && ch <= 13) || ch == 32);
}

int	is_num(char ch)
{
	return (ch >= 48 && ch <= 57);
}

long	ft_atol(char *str)
{
	long	nbr;

	nbr = 0;
	while (*str && is_space(*str))
		str++;
	while (*str && *str == '+')
		str++;
	if (*str == '-')
		return (error_exit("Invalid input: negative number"));
	if (!is_num(*str))
		return (error_exit("Invalid input: none-numeric type"));
	while (is_num(*str))
	{
		nbr = nbr * 10 + (*str - 48);
		str++;
	}
	if (*str && !is_num(*str))
		return (error_exit("Invalid input: Non-numeric type"));
	if (nbr > INT_MAX)
		return (error_exit("Invalid input: number too large"));
	return (nbr);
}

int	parse_input(t_data *data, char **ag)
{
	int	i;

	i = 0;
	while (ag[++i])
	{
		if (ft_atol(ag[i]) == -1)
			return (free(data), -1);
	}
	if (ft_atol(ag[1]) == 0)
		return (error_exit("Zero philo input"));
	data->philo_nbr = ft_atol(ag[1]);
	data->time_to_die = ft_atol(ag[2]);
	data->time_to_eat = ft_atol(ag[3]);
	data->time_to_sleep = ft_atol(ag[4]);
	if (ag[5])
	{
		if (ft_atol(ag[5]) == 0)
			return (-1);
		data->meal_max_limit = ft_atol(ag[5]);
	}
	else
		data->meal_max_limit = -1;
	data->end_flag = 0;
	return (0);
}
