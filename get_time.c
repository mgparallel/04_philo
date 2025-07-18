#include "philo.h"

long long get_time_ms(void)
{
	struct timeval tv;
	long long timestamp;

	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
	return (timestamp);
}