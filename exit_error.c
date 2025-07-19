#include "philo.h"

void	error_exit(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

void	mutex_error(int status, t_mutex_op op)
{
		if (status == 0)
			return ;
		if (status == EINVAL && (op == LOCK || op == UNLOCK || op == DESTORY))
			error_exit("Invalid or uninitialized mutex");
		else if (status == EINVAL && op == INIT)
			error_exit("The attributes object referenced by attr has the robust mutex \\
						attribute set without the process-shared attribute being set");
		else if (status == ENOMEM)
			error_exit("Insufficient memory exists to initialize the mutex");
		else if (status == EPERM)
			error_exit("The caller does not have the privilege to perform the operation");
		else if (status == EDEADLK)
			error_exit("deadlock condition was detected");
		else if (status == EBUSY)
			error_exit("The mutex could not be acquired because it was already locked");
}