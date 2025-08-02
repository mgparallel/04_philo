#include "philo_bonus.h"

// int	print_msg_util(t_philo *philo)
// {
// 	sem_wait(philo->core->sems->die_sem);
// 	if (philo->core->end_flag)
// 	{
// 		sem_post(philo->sem->);
// 		return (1);
// 	}
// 	sem_post(philo->sem->);
// 	return (0);
// }

// void	multi_write()
// {
// 	write(time);
// 	write ( philo->id)
// 	write ("%ld %d is eating\n", )
// }

void	print_msg(t_philo *philo, t_mode mode)
{
	long	time;

	if (mode != DIED)
		exit(EXIT_SUCCESS);
	sem_wait(philo->sem->write_sem);
	time = get_time_mc() - philo->start_time;
	if (mode == EAT)
		write("%ld %d is eating\n", time, philo->id);
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
	sem_post(philo->sem->write_sem);
}

int	main(int ac, char **ag)
{
	t_core *core;

	if (ac != 5 && ac != 6)
		error_exit("Incorrect number of arguments");
	core = safe_malloc(sizeof(t_core));
	parse_input();
	data_init();
	dinner_simu();

}