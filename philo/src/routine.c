/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazaouya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:56:05 by hazaouya          #+#    #+#             */
/*   Updated: 2022/06/21 19:31:16 by hazaouya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->phdata->forks + philo->left_fork);
	print_msg(philo, "has taken a left fork");
	pthread_mutex_lock(philo->phdata->forks + philo->right_fork);
	print_msg(philo, "has taken a right fork");
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->phdata->forks + philo->left_fork);
	pthread_mutex_unlock(philo->phdata->forks + philo->right_fork);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->le_chr);
	philo->last_eat = get_time();
	philo->is_eating = 1;
	if (philo->phdata->eat_num != -1)
		philo->nb_eat++;
	pthread_mutex_unlock(&philo->le_chr);
	print_msg(philo, "is eating");
	ft_usleep(get_time() + philo->phdata->t_eat);
	pthread_mutex_lock(&philo->le_chr);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->le_chr);
}

void	sleeping(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	ft_usleep(get_time() + philo->phdata->t_sleep);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		lock_forks(philo);
		eating(philo);
		unlock_forks(philo);
		sleeping(philo);
		print_msg(philo, "is thinking");
	}
	return (NULL);
}
