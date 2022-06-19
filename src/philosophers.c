#include "../includes/philosophers.h"

void	ft_usleep(int k)
{
	long res;

	res = get_time() + k;
	while (get_time() < res)
		usleep(100);
}

void	printf_msg(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->phdata->print);
	printf("%ld ms %d %s\n", get_time() - philo->phdata->t_start, philo->id, s);
	pthread_mutex_unlock(&philo->phdata->print);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->phdata->mutex[philo->left_fork]);
	printf_msg(philo, "has taken a left fork ");
	pthread_mutex_lock(&philo->phdata->mutex[philo->right_fork]);
	printf_msg(philo,"has taken a right fork ");
}

void	puts_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->phdata->mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->phdata->mutex[philo->right_fork]);
}

void	eating(t_philo *philo)
{
	philo->last_eat = get_time();
	printf_msg(philo, "is eating");
	philo->nb_eat++;
	philo->is_eating = 1;
	ft_usleep(philo->phdata->t_eat);
	philo->is_eating = 0;
	puts_forks(philo);
}

void	sleeping(t_philo *philo)
{
	printf_msg(philo, "is sleeping");
	ft_usleep(philo->phdata->t_sleep);
	printf_msg(philo, "is thinkig");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		take_forks(philo);
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}

void	ft_philos(t_phdata *phdata)
{
    int i;
	t_philo *temp;
	t_philo *temp2;

    i = 0;
	temp = phdata->philo;
    while(i < phdata->philo_num)
    {        
        pthread_create(&temp->thr, NULL, routine, temp);
		temp = temp->next;
		usleep(100);
		i++;
    }
	i = 0;
	int count;
	while (1)
	{
		i = 0;
		temp = phdata->philo;
		while (i < phdata->philo_num)
		{
			if (get_time() - temp->last_eat >= phdata->t_die)
			{
				printf_msg(temp, "Die");
				return ;
			}
			temp = temp->next;
			i++;
		}
		i = 0;
		count = 0;
		temp2 = phdata->philo;
		while (i < phdata->philo_num && temp->phdata->eat_num != -1)
		{
			if (temp2->nb_eat == temp2->phdata->eat_num)
				count++;
			i++;
			temp2 = temp2->next;
		}
		if (count == phdata->philo->nb_eat)
			return ;
	}
	
	while(i < phdata->philo_num)
    {
        pthread_join(temp->thr, NULL);
		temp = temp->next;
		i++;
    }

}