#include "../includes/philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, get_time(philo->start_time), "take RIGHT fork");
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, get_time(philo->start_time), "take LEFT fork");
}

void	philo_eating(t_philo *philo)
{
	print_status(philo, get_time(philo->start_time), "eating");
	++philo->count_eat;
	philo->time_life = get_time(0);
	my_usleep(philo->t2e);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleeping(t_philo *philo)
{
	print_status(philo, get_time(philo->start_time), "sleeping");
	my_usleep(philo->t2s);
}

void	philo_thinking(t_philo *philo)
{
	print_status(philo, get_time(philo->start_time), "thinking");
}

void	*philo(void *philo)
{
	t_philo	*philosoph;

	philosoph = (t_philo *)philo;
	if (philosoph->index % 2 == 0)
		my_usleep(philosoph->t2e / 2);
	while (1)
	{
		take_fork(philosoph);
		philo_eating(philosoph);
		philo_sleeping(philosoph);
		philo_thinking(philosoph);
	}
}
