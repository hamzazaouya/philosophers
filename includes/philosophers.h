#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "libft/libft.h"

typedef struct philosopher {
	long			t_die;
	int				t_eat;
	int				t_sleep;
	int				position;
	pthread_mutex_t left_fork;
	pthread_mutex_t right_fork;
	struct philosopher *next;
}t_philosopher;



typedef struct phdata
{
	pthread_mutex_t	*mutex;
	t_philosopher	*philosopher;
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_num;
}	t_phdata;

void	lstadd_back(t_philosopher **lst, t_philosopher *new);
long	ft_get_time();

#endif
