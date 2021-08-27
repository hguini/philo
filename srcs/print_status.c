#include "../includes/philo.h"

void	print_status(t_philo *philo, size_t time, char *message)
{
	pthread_mutex_lock(&philo->all->block_write_chat);
	printf("%zu Philo %d: %s\n", time, philo->index + 1, message);
	if (!philo->is_dead)
		pthread_mutex_unlock(&philo->all->block_write_chat);
}
