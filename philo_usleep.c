#include "philo.h"

void philo_usleep(long time_ms)
{
	long start;

	start = get_time_mc();
	while (get_time_mc() - start < time_ms)
		usleep(100);
}