#include "philo.h"

int	error_exit(char *msg) //check to exit during parse_input
{
	printf("%s\n", msg);
	return (-1);
}

int	mutex_error(int status, t_mutex_op op)
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