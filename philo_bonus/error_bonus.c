#include "philo_bonus.h"

void	error_exit(t_core *core, char *msg)
{
	printf("%s\n", msg);
	destroy(core);
	exit (EXIT_FAILURE);
}

void	*safe_malloc(t_core *core, size_t size)
{
	void	*struc;

	struc = malloc(size);
	if (!struc)
		error_exit(core, "Failed malloc");
	return (struc);
}

void	*handle_sph_error(t_core *core, int status,  t_semcode *scode)
{
	if (status == 0)
		return ;
	if (status == EACCES && (scode == OPEN || scode == UNLINK))
		error_exit(core, "Premission denied");
	if (status == EEXIST && scode == OPEN)
		error_exit(core, "Semaphore exists");
	if (status == EINTR && (scode == OPEN || scode == WAIT))
		error_exit(core, "Sem_open interrupted by signal");
	if ((status == EMFILE || status == ENFILE || status == ENOSPC)
				&& scode == OPEN)
		error_exit(core, "Error with semaphore");
	if (status == EINVAL && scode != UNLINK)
		error_exit(core, "Invalid sem");
	if (status == ENAMETOOLONG && (scode == OPEN || scode == UNLINK))
		error_exit(core, "Name exceeded limit");
	if (status == ENOENT && (scode == OPEN || scode == UNLINK))
		error_exit(core, "Name doesn't exist");
	if (status == EDEADLK && scode == WAIT)
		error_exit(core, "A deadlock was detected");
	if (status == EAGAIN && scode == WAIT)
		error_exit(core, "The semaphore is already locked");
	else
		error_exit(core, "Unknown error");
}

void	safe_semaphore(t_core *core, t_semcode *scode, char *name)
{
	if (scode == CLOSE)
		handle_sph_error(core, sem_close(name), CLOSE);
	if (scode == UNLINK)
		handle_sph_error(core, sem_unlink(name), UNLINK);
	if (scode == WAIT)
		handle_sph_error(core, sem_wait(name), WAIT);
	if (scode == POST)
		handle_sph_error(core, sem_post(name), POST);
}
 