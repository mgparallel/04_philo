#include "philo_bonus.h"

void	multi_write(long time, int id, char *str, t_mode mode)
{
	char *t;
	char *i;
	int	len_t;
	int len_i;
	int len_str;

	len_t = 0;
	len_i = 0;
	len_str = 0;
	t = ft_itoa(time);
	i = ft_itoa((long)id);
	while (t[len_t])
		len_t++;
	while (i[len_i])
		len_i++;
	write(1, &t, len_t);
	write (1, " ", 1);
	write (1, &i, len_i);
	if (str)
	{
		while (str[len_str])
			len_str++;
	}
	if (mode == FORK)
		write (1, " has taken a fork\n", 17);
	else if (mode == DIED)
		write (1, " died\n", 5);
	else
		write (1, &str, len_str);
}

void	print_msg(t_philo *philo, t_mode mode)
{
	long	time;

	if (mode != DIED)
		exit(EXIT_SUCCESS);
	sem_wait(philo->sem->write_sem);
	time = get_time_mc() - philo->start_time;
	if (mode == EAT)
		multi_write(time, philo->id, " is eating\n", EAT);
	else if (mode == FORK)
		multi_write(time, philo->id, NULL, FORK);
	else if (mode == SLEEP)
		multi_write(time, philo->id, " is sleeping\n", SLEEP);
	else if (mode == THINK)
		multi_write(time, philo->id, " is thinking\n", THINK);
	else if (mode == DIED)
		multi_write(time, philo->id, NULL, DIED);
	else
		printf("Incorrect message type\n");
	sem_post(philo->sem->write_sem);
}

int	main(int ac, char **ag)
{
	t_core *core;

	if (ac != 5 && ac != 6)
		error_exit("Incorrect number of arguments");
	if (parse_input(core, ag) == -1)
		exit(EXIT_FAILURE);
	data_init(core);
	dinner_simu();

}