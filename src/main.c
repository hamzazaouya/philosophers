#include "../includes/philosophers.h"

long get_time()
{
	struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

t_philo	*creat_philos(t_phdata *phdata)
{
    int				i;
    t_philo	*philo;
    t_philo	*temp;

    i = 0;
    philo = ft_lstnew();
    temp = philo;
   
    while(i < phdata->philo_num)
    {
        if(i > 0)
			lstadd_back(&philo, ft_lstnew());
        temp = lstlast(philo);
        temp->id = i + 1;
        temp->nb_eat = 0;
        temp->phdata = phdata;
		temp->left_fork = i;
        temp->last_eat = get_time();
		if(i == phdata->philo_num - 1)
			temp->next = philo;
        temp->right_fork = (i + 1) % phdata->philo_num;
		i++;
    }
    return (philo);
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
        printf("->>%d\n",i);
        i++;
    }
    pthread_mutex_init(&phdata->print, NULL);
    return (phdata->mutex);
}

void ft_init(int argc, char **argv, t_phdata *phdata)
{
    (void)argc;
    phdata->philo_num = ft_atoi(argv[1]);
    phdata->t_die = ft_atoi(argv[2]);
    phdata->t_eat = ft_atoi(argv[3]);
    phdata->t_sleep = ft_atoi(argv[4]);
    if(argv[5])
        phdata->eat_num = ft_atoi(argv[5]);
    else
        phdata->eat_num = -1;
    phdata->mutex = ft_create_mutex(phdata);
    phdata->t_start = get_time();
    if(!phdata->mutex)
        return ;
    phdata->philo = creat_philos(phdata);
}

int main(int argc, char **argv) {
    t_phdata phdata;

    if(argc > 4)
    {
	    ft_init(argc, argv, &phdata);
        ft_philos(&phdata);
    }
    else
        printf("Less Argument \n");
    exit(0);
}