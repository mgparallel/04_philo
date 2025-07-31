#include "philo.h"

void	philo_init(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		philo[i].id = i + 1;
		philo[i].meal_counter = 0;
		philo[i].is_full = false;
		philo[i].is_eating = false;
		philo[i].last_meal_time = 0;
		philo[i].data = data;
		if (i % 2 == 0)
		{
			philo[i].first_fork = &data->fork[i];
			philo[i].second_fork = &data->fork[(i + 1) % data->philo_nbr];
		}
		else
		{
			philo[i].first_fork = &data->fork[(i + 1) % data->philo_nbr];
			philo[i].second_fork = &data->fork[i];
		}
		philo[i].dead_lock = &data->dead_lock;
		philo[i].write_lock = &data->write_lock;
		i++;
	}
}

void	data_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = safe_malloc(sizeof(t_philo) * data->philo_nbr);
	data->fork = safe_malloc(sizeof(t_mtx) * data->philo_nbr);
	data->end_flag = 0;
	safe_mutex(pthread_mutex_init(&(data->dead_lock), NULL), INIT);
	safe_mutex(pthread_mutex_init(&(data->write_lock), NULL), INIT);
	safe_mutex(pthread_mutex_init(&(data->meal_lock), NULL), INIT);
	while (i < data->philo_nbr)
	{
		safe_mutex(pthread_mutex_init(&data->fork[i], NULL), INIT);
		i++;
	}
	philo_init(data, philo);
	data->philo = philo;
}
