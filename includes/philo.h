#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_all	t_all;

typedef struct	s_philo
{
	int					index;
	int					t2d;
	int					t2e;
	int					t2s;
	int					count_eat;
	int 				is_dead;
	t_all				*all;
	ssize_t				time_life;
	ssize_t				start_time;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	// pthread_mutex_t		block_write_chat;
}				t_philo;

typedef struct	s_all
{
	int	count_philo;
	int	t2d;
	int	t2e;
	int	t2s;
	int	must_e;
	ssize_t			start_time;
	pthread_mutex_t *forks_arr;
	pthread_mutex_t	block_write_chat;
	t_philo	*philo;
}				t_all;

int	ft_atoi(char *str);


#endif
