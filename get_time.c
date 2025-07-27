#include "philo.h"

long long get_time_mc(void)
{
	struct timeval tv;
	long long timestamp;

	if (gettimeofday(&tv, NULL))
		error_exit("Failed calling gettimeofday()");
	timestamp = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
	return (timestamp);
}

// int main(void)
// {
// 	printf("time: %lld\n", get_time_ms());
// 	usleep(2000);
// 	printf("time: %lld\n", get_time_ms());
// 	return (0);
// }