#include "../includes/philo.h"

void	*monitoring(void *global)
{
	t_all	*all;
	int		i;

	all = (t_all *)global;
	while (1)
	{
		i = -1;
		all->fact_e = 0;
		while (++i < all->count_philo)
		{
			if (all->philo[i].count_eat >= all->must_e && all->must_e != -1)
				++all->fact_e;
			if (all->t2d < get_time(all->philo[i].time_life))
			{
				all->philo[i].is_dead = 1;
				print_status(&all->philo[i], get_time(all->start_time), "die");
				return (NULL);
			}
		}
		if (all->fact_e == all->count_philo)
		{
			pthread_mutex_lock(&all->block_write_chat);
			return (NULL);
		}
	}
}
