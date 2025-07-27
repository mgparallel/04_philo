#include "philo.h"

int is_space(char ch)
{
	return ((ch >= 9 && ch <= 13) || ch == 32);
}

int is_num(char ch)
{
	return (ch >= 48 && ch <= 57);
}

long ft_atol(char *str) // "   +77uas"
{
	long nbr;

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
	if (nbr > INT_MAX)
		return (error_exit("Invalid input: number too large"));
	return (nbr);
}

//   0          1                       2             3             4             5
// ./philo,  number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [must_eat_count]
int parse_input(t_data *data, char **ag)
{
	int i;

	i = 0;
	while (ag[++i])
	{
		if (ft_atol(ag[i]) == -1)
			return (free(data), -1);
	}
	data->philo_nbr = ft_atol(ag[1]);
	data->time_to_die = ft_atol(ag[2]);
	data->time_to_eat = ft_atol(ag[3]);
	data->time_to_sleep = ft_atol(ag[4]);
	if (ag[5])
		data->meal_max_limit = ft_atol(ag[5]);
	else
		data->meal_max_limit = -1;
	data->end_flag = 0;
	return (0);
}