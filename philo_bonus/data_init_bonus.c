#include "philo_bonus.h"

void	philo_init(t_core *core, t_philo **philo)
{
		int i;

		i = 0;
		while (i < core->philo_nbr)
		{
			philo[i] = safe_malloc(core, sizeof(t_philo));
			philo[i]->id = i + 1;
			philo[i]->start_time = get_time_mc();
			philo[i]->last_meal_time = get_time_mc();
			philo[i]->meal_counter = 0;
			philo[i]->is_eating = false;
			philo[i]->sem = core->sems;
			philo[i]->core = core;
			i++;
		}
}

void	sems_init(t_core *core, t_sem *sems)
{
		sems->die_sem = sem_open(DIE_SEM, O_CREAT | O_EXCL, 0644, 1);
		handle_sph_error(core, sems->die_sem, OPEN);
		sems->meal_sem = sem_open(MEAL_SEM, O_CREAT | O_EXCL, 0644, 0);
		handle_sph_error(core, sems->meal_sem, OPEN);
		sems->fork_sem = sem_open(FORK_SEM, O_CREAT | O_EXCL, 0644, core->philo_nbr);
		handle_sph_error(core, sems->fork_sem, OPEN);
		sems->write_sem = sem_open(WRITE_SEM, O_CREAT | O_EXCL, 0644, 1);
		handle_sph_error(core, sems->write_sem, OPEN);
		safe_semaphore(core, UNLINK, DIE_SEM);
		safe_semaphore(core, UNLINK, MEAL_SEM);
		safe_semaphore(core, UNLINK, FORK_SEM);
		safe_semaphore(core, UNLINK, WRITE_SEM);
}

void	data_init(t_core *core)
{
	t_philo **philo;
	t_sem 	*sems;
	pid_t	*pids;
	int i;

	i = 0;
	philo = safe_malloc(core, sizeof(t_philo *) * (core->philo_nbr));
	sems = safe_malloc(core, sizeof(t_sem));
	pids = safe_malloc(core, sizeof(pid_t) * (core->philo_nbr));
	while (i < core->philo_nbr)
	{
		pids[i] = -1;
		philo[i] = NULL;
		i++;
	}
	sems_init(core, core->sems);
	philo_init(core, philo);
	core->philo = philo;
	core->sems = sems;
	core->pids = pids;
	core->end_flag = 0;
}