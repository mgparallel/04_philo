/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:19:23 by menwu             #+#    #+#             */
/*   Updated: 2025/07/31 22:42:35 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mtx;

typedef enum mode
{
	EAT,
	SLEEP,
	THINK,
	FORK,
	DIED,
}						t_mode;

typedef enum pcode
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
	CREATE,
	JOIN,
	DETACH,
}						t_pcode;

typedef struct s_philo
{
	int					id;
	int					meal_counter;
	bool				is_full;
	bool				is_eating;
	long				last_meal_time;
	pthread_t			thread_id;
	t_mtx				*first_fork;
	t_mtx				*second_fork;
	t_mtx				*dead_lock;
	t_mtx				*write_lock;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	meal_max_limit;
	long	start_time;
	int		end_flag;
	t_mtx	*fork;
	t_mtx	dead_lock;
	t_mtx	write_lock;
	t_mtx	meal_lock;
	t_philo	*philo;
}				t_data;

long long		get_time_mc(void);
void			philo_usleep(t_data *data, long time_ms);
void			print_msg(t_philo *philo, t_mode mode);
int				error_exit(char *msg);
void			*safe_malloc(size_t size);
int				safe_mutex(int status, t_pcode op);
int				safe_thread_handle(pthread_t *thread,
					void *(*f)(void *), void *philo, t_pcode op);
int				parse_input(t_data *data, char **ag);
void			data_init(t_data *data);
int				dinner_start(t_data *data);
void			eat_mode(t_philo *philo);
void			sleep_mode(t_philo *philo);
void			think_mode(t_philo *philo);
int				philo_died(t_philo *philo);
void			*monitor(void *arg);
void			destroy(t_data *data, t_mtx *fork);

#endif