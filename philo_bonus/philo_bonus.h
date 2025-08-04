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
# include <semaphore.h>

# define DIE_SEM "/die_sem"
# define MEAL_SEM "/meal_sem"
# define FORK_SEM "/fork_sem"
# define WRITE_SEM "/write_sem"

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
	//bool				is_full;// needed?
	bool				is_eating;
	t_sem				*sem;
	t_core				*core;
}						t_philo;

typedef struct s_core
{
		long	philo_nbr; //parse
		t_philo **philo; //init
		t_sem	*sems;//init
		pid_t	*pids;//init
		long	time_to_die; //parse
		long	time_to_eat; //parse
		long	time_to_sleep; //parse
		long	meal_max_limit; //parse
		int		end_flag;
}				t_core;

void	print_msg(t_philo *philo, t_mode mode);
void	error_exit(char *msg);
void	destroy(t_core *core);
long long	get_time_mc(void);
void	philo_usleep(t_core *core, long time_ms);
void	safe_semaphore(t_core *core, t_semcode *scode, char *name);
void	*handle_sph_error(t_core *core, int status,  t_semcode *scode);
char	*ft_itoa(long n);
int		parse_input(t_core *core, char **ag);
void	*safe_malloc(t_core *core, size_t size);
void	data_init(t_core *core);

# endif