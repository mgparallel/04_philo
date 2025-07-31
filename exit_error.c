#include "philo.h"

int	error_exit(char *msg) // check to exit during parse_input
{
	printf("%s\n", msg);
	return (-1);
}

void	*safe_malloc(size_t size)
{
	void	*struc;

	struc = malloc(size);
	if (!struc)
	{
		printf("Failed malloc\n");
		return (NULL);
	}
	return (struc);
}

int	safe_mutex(int status, t_pcode op)
{
	if (status == 0)
		return (0);
	if (status == EINVAL && (op == LOCK || op == UNLOCK || op == DESTROY))
		return (error_exit("Invalid or uninitialized mutex"));
	else if (status == EINVAL && op == INIT)
		return (error_exit("Invalid mutex attribute being set"));
	else if (status == ENOMEM)
		return (error_exit("Insufficient memory exists to initialize the mutex"));
	else if (status == EPERM)
		return (error_exit("The caller does not have the privilege to perform the operation"));
	else if (status == EDEADLK && op == LOCK)
		return (error_exit("deadlock condition was detected"));
	else if (status == EBUSY && op == DESTROY)
		return (error_exit("Mutex is currently locked and cannot be destroyed"));
	else
		return (error_exit("Unknow error"));
}

int	handle_thread_error(int status, t_pcode op)
{
	if (status == 0)
		return (0);
	if (status == EAGAIN && op == CREATE)
		return (error_exit("Lack of resources to create thread"));
	if (status == EPERM && op == CREATE)
		return (error_exit("No permission"));
	if (status == EINVAL && op == CREATE)
		return (error_exit("Invalid attribute value"));
	return (0);
}

int	safe_thread_handle(pthread_t *thread, void *(*f)(void *), void *philo,
		t_pcode op)
{
	int status;

	status = 0;
	if (op == CREATE)
	{
		status = pthread_create(thread, NULL, f, philo);
		return (handle_thread_error(status, CREATE) == -1);
	}
	else if (op == JOIN)
	{
		status = pthread_join(*thread, NULL);
		return (handle_thread_error(status, JOIN) == -1);
	}
	else if (op == DETACH)
	{
		status = pthread_detach(*thread);
		return (handle_thread_error(status, DETACH) == -1);
	}
	else
		return (error_exit("Incorrect threads handling"));
}