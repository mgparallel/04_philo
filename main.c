#include "philo.h"

void	print_msg(t_philo *philo, t_mode mode)
{
	long	time;

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

// 0               1              2             3             4               5
// ./philo,  number_of_philo, time_to_die, time_to_eat, time_to_sleep,
	[must_eat_count]

int	main(int ac, char **ag)
{
	t_data *data;

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