/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazaouya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:08:44 by hazaouya          #+#    #+#             */
/*   Updated: 2022/06/21 19:28:23 by hazaouya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->phdata->print);
	printf("%ld %d %s\n", get_time() - philo->phdata->t_start, philo->id, msg);
	pthread_mutex_unlock(&philo->phdata->print);
}

void	ft_usleep(long time)
{
	while (get_time() < time)
		usleep(100);
}

int	control_eating(t_phdata *phdata)
{
	int	i;

	i = 0;
	while (i < phdata->philo_num)
	{
		pthread_mutex_lock(&phdata->philo[i].le_chr);
		if (phdata->philo[i].nb_eat != phdata->eat_num)
		{
			pthread_mutex_unlock(&phdata->philo[i].le_chr);
			return (0);
		}
		pthread_mutex_unlock(&phdata->philo[i].le_chr);
		i++;
	}
	return (1);
}

void	ft_supervisor(t_phdata *phdata)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < phdata->philo_num)
		{
			pthread_mutex_lock(&phdata->philo[i].le_chr);
			if (get_time() - phdata->philo[i].last_eat >= phdata->t_die \
					&& !phdata->philo[i].is_eating)
			{
				pthread_mutex_lock(&phdata->print);
				printf("%ld %d %s\n", get_time() - phdata->t_start, \
						phdata->philo[i].id, "died");
				return ;
			}
			pthread_mutex_unlock(&phdata->philo[i].le_chr);
			i++;
		}
		if (phdata->eat_num != -1)
			if (control_eating(phdata))
				return ;
		usleep(500);
	}
}

void	ft_philos(t_phdata *phdata)
{
	int	i;

	i = 0;
	while (i < phdata->philo_num)
	{
		pthread_create(&phdata->philo[i].thr, NULL, routine, phdata->philo + i);
		usleep(100);
		i++;
	}
	ft_supervisor(phdata);
	return ;
}
