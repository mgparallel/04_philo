#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data t_data;

typedef enum mutex_op
{
	INIT,
	DESTORY,
	LOCK,
	UNLOCK,
}	t_mutex_op;

typedef struct s_mtx
{
	pthread_mutex_t	*mutex;
	int				is_locked;
}					t_mtx;

typedef struct s_fork
{
	int				fork_id;
	t_mtx			fork;
}					t_fork;

typedef struct s_philo
{
	int				id;
	int				mean_counter;
	bool			is_full;
	long			last_meal;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	t_data			*data;
}					t_philo;

typedef struct s_data
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meal_max_limit;
	long			init;
	bool			is_end;
	t_fork			*fork;
	t_philo			*philo;
}					t_data;


void error_exit(char *msg);
int parse_input(t_data *data, char **ag);


#endif