#include "philo.h"

// 0          1                       2             3             4               5
// ./philo,  number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [must_eat_count]
int main(int ac, char **ag)
{
	if (ac == 5 || ac == 6)
	{
		//check if input is valid
		parse_input();
		//assign data into the stucture, initiate the round
		data_init();
		//
		dinner_start();
		//clean
		clean();
	}
	else
		exit_error();
	return (0);
}