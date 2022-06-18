#include "../includes/philosophers.h"

long ft_get_time()
{
	struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

t_philosopher	*creat_philos(t_phdata *phdata)
{
    int				i;
    t_philosopher	*philosopher;
    t_philosopher	*temp;

    i = 0;
    philosopher = (t_philosopher *) malloc(sizeof(t_philosopher));
    temp = philosopher;
    while(i < phdata->philo_num)
    {
        if(i > 0)
		{
            temp = (t_philosopher *) malloc(sizeof(t_philosopher));
			lstadd_back(&philosopher, temp);
		}
        temp->position = i;
        temp->t_die = ft_get_time() + phdata->time_to_die;
		temp->t_eat = phdata->time_to_eat * 1000;
		temp->t_sleep = phdata->time_to_sleep * 1000;
		temp->left_fork = phdata->mutex[i];
		if(i == phdata->philo_num)
			temp->next = philosopher;
        temp->right_fork = phdata->mutex[(i + 1) % phdata->philo_num];
		i++;
    }
    return (philosopher);
}

pthread_mutex_t *ft_create_mutex(t_phdata *phdata)
{
    int i;

    i = 0;
    phdata->mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * phdata->philo_num);
    if(!phdata->mutex)
        return (NULL);
    while(i < phdata->philo_num)
    {
        pthread_mutex_init(&phdata->mutex[i], NULL);
        i++;
    }
    return (phdata->mutex);
}

void ft_init(int argc, char **argv, t_phdata *phdata)
{
    phdata->philo_num = ft_atoi(argv[1]);
    phdata->time_to_die = ft_atoi(argv[2]);
    phdata->time_to_eat = ft_atoi(argv[3]);
    phdata->time_to_sleep = ft_atoi(argv[4]);
    phdata->eat_num = ft_atoi(argv[5]);
    phdata->mutex = ft_create_mutex(phdata);
    if(!phdata->mutex)
        return ;
    phdata->philosopher = creat_philos(phdata);
}

int main(int argc, char **argv) {
    t_phdata phdata;

    if(argc > 5)
    {
	    ft_init(argc, argv, &phdata);
        ft_philosophers(phdata);
    }
    else
        printf("Less Argument \n");
  return 0;
}