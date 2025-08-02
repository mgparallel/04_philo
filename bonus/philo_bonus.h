#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
#include <semaphore.h>

typedef struct s_philo	t_philo;
typedef struct s_core	t_core;

typedef enum mode
{
	EAT,
	SLEEP,
	THINK,
	FORK,
	DIED,
}						t_mode;

typedef enum semcode
{
	OPEN,
	CLOSE,
	UNLINK,
	WAIT,
	POST,
}						t_semcode;

typedef struct s_sem
{
		sem_t 	*fork_sem;
		sem_t 	*meal_sem;
		sem_t 	*write_sem;
		sem_t 	*die_sem;
}				t_sem;

typedef struct s_philo
{
	int					id;
	long				start_time;
	long				last_meal_time;
	int					meal_counter;
	bool				is_full;// needed?
	bool				is_eating;
	t_sem				*sem;
	t_core				*core;
}						t_philo;

typedef struct s_core
{
		long	philo_nbr;
		t_philo **philo;
		t_sem	*sems;
		pid_t	*p_id;
		long	time_to_die;
		long	time_to_eat;
		long	time_to_sleep;
		long	meal_max_limit;
}				t_core;

void	print_msg(t_philo *philo, t_mode mode);


# endif