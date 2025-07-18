#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data
{
	int id;
	int fst_fork;
	int scd_fork;
	long long last_meal_time;
	int means_count;
	pthread_mutex_t *forks;
} t_data;

# endif