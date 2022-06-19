#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "libft/libft.h"

struct philosopher;

typedef struct phdata
{
	pthread_mutex_t	*mutex;
	struct philosopher	*philo;
	int	philo_num;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	eat_num;
	long	t_start;
	pthread_mutex_t print;
}	t_phdata;

typedef struct philosopher {
	int				id;
	int				is_eating;
	long			last_eat;
	int				nb_eat;
	t_phdata		*phdata;
	pthread_t		thr;
	int				left_fork;
	int				right_fork;
	struct philosopher *next;
}	t_philo;


void	lstadd_back(t_philo **lst, t_philo *new);
t_philo	*lstlast(t_philo *lst);
t_philo	*ft_lstnew(void);
long	get_time();
void	ft_philos(t_phdata *phdata);

#endif
