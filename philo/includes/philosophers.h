/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazaouya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:56:49 by hazaouya          #+#    #+#             */
/*   Updated: 2022/06/21 18:02:52 by hazaouya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_philosopher;

typedef struct phdata
{
	pthread_mutex_t			*forks;
	struct s_philosopher	*philo;
	int						philo_num;
	int						t_die;
	int						t_eat;
	int						t_sleep;
	int						eat_num;
	long					t_start;
	int						*eat_chkr;
	pthread_mutex_t			print;
}	t_phdata;

typedef struct s_philosopher {
	int				id;
	int				is_eating;
	long			last_eat;
	int				nb_eat;
	t_phdata		*phdata;
	pthread_t		thr;
	int				left_fork;
	int				right_fork;
	pthread_mutex_t	le_chr;
}	t_philo;

int		ft_atoi(const char *str);
long	get_time(void);
void	ft_philos(t_phdata *phdata);
void	*ft_calloc(size_t count, size_t size);
void	*routine(void *arg);
void	print_msg(t_philo *philo, char *msg);
void	ft_usleep(long time);

#endif
