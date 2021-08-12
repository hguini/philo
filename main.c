#include "includes/philo.h"

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
	// all->philo[i].block_write_chat = all->block_write_chat;
	all->philo[i].thread = name_thread[i];
	all->philo[i].count_eat = 0;
}

void	print_status(t_philo *philo, size_t time, char *message)
{
	// printf("%d\n", philo->all->t2d);
	pthread_mutex_lock(&philo->all->block_write_chat);
	printf("%zu Philo %d: %s\n", time, philo->index, message);
	if (!philo->is_dead)
		pthread_mutex_unlock(&philo->all->block_write_chat);
}

void	take_fork(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, get_time(philo->start_time), "take RIGHT fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, get_time(philo->start_time), "take LEFT fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, get_time(philo->start_time), "take LEFT fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, get_time(philo->start_time), "take RIGHT fork");
	}
}

void	philo_eating(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		print_status(philo, get_time(philo->start_time), "eating");
		++philo->count_eat;
		philo->time_life = get_time(0);
		my_usleep(philo->t2e);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		print_status(philo, get_time(philo->start_time), "eating");
		++philo->count_eat;
		philo->time_life = get_time(0);
		my_usleep(philo->t2e);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
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
	t_philo *philosoph;

	philosoph = (t_philo *)philo;
	pthread_detach(philosoph->thread);
	while(1)
	{
		take_fork(philosoph);
		philo_eating(philosoph);
		philo_sleeping(philosoph);
		philo_thinking(philosoph);
	}
}

void	*monitoring(void *global)
{
	t_all *all;
	int i;

	all = (t_all *)global;
	while(1)
	{
		i = 0;
		while (i < all->count_philo)
		{
			if (all->t2d < get_time(all->philo[i].time_life) || \
				all->philo[i].count_eat == all->must_e)
			{
				all->philo->is_dead = 1;
				print_status(all->philo, get_time(all->start_time), "die");
				return (NULL);
			}
			++i;
		}
	}
}

void	start_philo(t_all *all)
{
	pthread_t		check_death;
	pthread_t		*philosophs;
	int i;

	all->forks_arr = malloc(sizeof(pthread_mutex_t) * all->count_philo);
	all->philo = malloc(sizeof(t_philo) * all->count_philo);
	philosophs = malloc(sizeof(pthread_t) * all->count_philo);
	i = 0;
	while(i < all->count_philo)
	{
		pthread_mutex_init(&all->forks_arr[i], NULL);
		++i;
	}
	i = 0;
	pthread_mutex_init(&all->block_write_chat, NULL);
	while (i < all->count_philo)
	{
		get_values(all, i, philosophs);
		all->philo[i].index = i;
		pthread_create(&philosophs[i], NULL, philo, (void *)(&all->philo[i]));
		++i;
	}
	pthread_create(&check_death, NULL, monitoring, all);
	pthread_join(check_death, NULL);
	pthread_detach(check_death);
	free(all->forks_arr);
	free(all->philo);
	free(philosophs);
}

void	init_arg(t_all *all, char **arg)
{
	all->count_philo = ft_atoi(arg[1]);
	all->t2d = ft_atoi(arg[2]);
	all->t2e = ft_atoi(arg[3]);
	all->t2s = ft_atoi(arg[4]);
	if (arg[5] != NULL)
		all->must_e = ft_atoi(arg[5]);
	else
		all->must_e = -1;
}

int	main(int argc, char **argv)
{
	t_all *all;

	all = malloc(sizeof(t_all));
	all->start_time = get_time(0);
	if (argc < 5 || argc > 6)
		printf("Invalid arguments");
	else
	{
		init_arg(all, argv);
		start_philo(all);
	}
	free(all);
	return(0);
}