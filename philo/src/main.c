/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazaouya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:53:58 by hazaouya          #+#    #+#             */
/*   Updated: 2022/06/21 16:02:42 by hazaouya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_philo	*creat_philos(t_phdata *phdata)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *) malloc(sizeof(t_philo) * phdata->philo_num);
	while (i < phdata->philo_num)
	{
		philo[i].id = i + 1;
		philo[i].nb_eat = 0;
		philo[i].is_eating = 0;
		philo[i].phdata = phdata;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % phdata->philo_num;
		philo[i].last_eat = get_time();
		pthread_mutex_init(&philo[i].le_chr, NULL);
		i++;
	}
	return (philo);
}

pthread_mutex_t	*ft_create_mutex(t_phdata *phdata)
{
	int	i;

	i = 0;
	phdata->forks = (pthread_mutex_t *) \
					malloc(sizeof(pthread_mutex_t) * phdata->philo_num);
	if (!phdata->forks)
		return (NULL);
	while (i < phdata->philo_num)
	{
		pthread_mutex_init(&phdata->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&phdata->print, NULL);
	return (phdata->forks);
}

int	ft_check_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_atoi(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_init(char **argv, t_phdata *phdata)
{
	if (!ft_check_args(argv))
		return (0);
	phdata->philo_num = ft_atoi(argv[1]);
	phdata->t_die = ft_atoi(argv[2]);
	phdata->t_eat = ft_atoi(argv[3]);
	phdata->t_sleep = ft_atoi(argv[4]);
	phdata->eat_chkr = (int *)ft_calloc(phdata->philo_num, sizeof(int));
	if (argv[5])
		phdata->eat_num = ft_atoi(argv[5]);
	else
		phdata->eat_num = -1;
	phdata->forks = ft_create_mutex(phdata);
	phdata->t_start = get_time();
	if (!phdata->forks)
		return (1);
	phdata->philo = creat_philos(phdata);
	return (1);
}

int	main(int argc, char **argv)
{
	t_phdata	*phdata;

	phdata = malloc(sizeof(t_phdata));
	if (argc == 5 || argc == 6)
	{
		if (!ft_init(argv, phdata))
			return (0);
		ft_philos(phdata);
	}
	return (0);
}
