#include "../includes/philo.h"

ssize_t	get_time(ssize_t start_time)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	return ((t1.tv_sec * 1000 + t1.tv_usec / 1000) - start_time);
}

void	my_usleep(ssize_t time)
{
	time_t	start;
	time_t	end;

	start = get_time(0);
	end = get_time(0) + time;
	while (start < end)
	{
		usleep(100);
		start = get_time(0);
	}
}
