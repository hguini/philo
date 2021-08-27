#include "includes/philo.h"

void	get_values(t_all *all, int i, pthread_t *name_thread)
{
	all->philo[i].t2d = all->t2d;
	all->philo[i].t2e = all->t2e;
	all->philo[i].t2s = all->t2s;
	all->philo[i].start_time = all->start_time;
	all->philo[i].index = i;
	all->philo[i].is_dead = 0;
	all->philo[i].time_life = get_time(0);
	all->philo[i].left_fork = &all->forks_arr[i];
	all->philo[i].right_fork = &all->forks_arr[(i + 1) % all->count_philo];
	all->philo[i].all = all;
	all->philo[i].thread = name_thread[i];
	all->philo[i].count_eat = 0;
}

void	start_philo(t_all *all)
{
	pthread_t		check_death;
	pthread_t		*philosophs;
	int				i;

	all->forks_arr = malloc(sizeof(pthread_mutex_t) * all->count_philo);
	all->philo = malloc(sizeof(t_philo) * all->count_philo);
	philosophs = malloc(sizeof(pthread_t) * all->count_philo);
	i = -1;
	while (++i < all->count_philo)
		pthread_mutex_init(&all->forks_arr[i], NULL);
	i = -1;
	pthread_mutex_init(&all->block_write_chat, NULL);
	while (++i < all->count_philo)
	{
		get_values(all, i, philosophs);
		all->philo[i].index = i;
		pthread_create(&philosophs[i], NULL, philo, (void *)(&all->philo[i]));
	}
	pthread_create(&check_death, NULL, monitoring, all);
	pthread_join(check_death, NULL);
	pthread_detach(check_death);
	free(all->forks_arr);
	free(all->philo);
	free(philosophs);
}

int	init_arg(t_all *all, char **arg)
{
	all->count_philo = ft_atoi(arg[1]);
	all->t2d = ft_atoi(arg[2]);
	all->t2e = ft_atoi(arg[3]);
	all->t2s = ft_atoi(arg[4]);
	if (arg[5] != NULL)
		all->must_e = ft_atoi(arg[5]);
	else
		all->must_e = -1;
	if (all->count_philo && all->t2d && all->t2e && \
		all->t2s && (all->must_e == -1 || all->must_e))
		return (0);
	else
		return (1);
}

int	main(int argc, char **argv)
{
	t_all	*all;

	all = malloc(sizeof(t_all));
	all->start_time = get_time(0);
	if (argc < 5 || argc > 6 || init_arg(all, argv))
		printf("Invalid arguments");
	else
		start_philo(all);
	free(all);
	return (0);
}
