/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:33:18 by menwu             #+#    #+#             */
/*   Updated: 2025/08/04 08:35:05 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		error_exit("Invalid input: negative number");
	if (!is_num(*str))
		error_exit("Invalid input: none-numeric type");
	while (is_num(*str))
	{
		nbr = nbr * 10 + (*str - 48);
		str++;
	}
	if (*str && !is_num(*str))
		error_exit("Invalid input: Non-numeric type");
	if (nbr > INT_MAX)
		error_exit("Invalid input: number too large");
	return (nbr);
}

int	parse_input(t_core *core, char **ag)
{
	int	i;

	i = 0;
	core = safe_malloc(core, sizeof(t_core));
	while (ag[++i])
	{
		if (ft_atol(ag[i]) == -1)
			return (-1);
	}
	if (ft_atol(ag[1]) == 0)
		error_exit("Zero philo input");
	core->philo_nbr = ft_atol(ag[1]);
	core->time_to_die = ft_atol(ag[2]);
	core->time_to_eat = ft_atol(ag[3]);
	core->time_to_sleep = ft_atol(ag[4]);
	if (ag[5])
	{
		if (ft_atol(ag[5]) == 0)
			return (-1);
		core->meal_max_limit = ft_atol(ag[5]);
	}
	else
		core->meal_max_limit = -1;
	return (0);
}
