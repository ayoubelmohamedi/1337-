
#include "ft_philo_bonus.h"


void ft_usleep(size_t time_to_sleep)
{
	size_t current = current_time_in_milliseconds();
	while (current_time_in_milliseconds() - current < time_to_sleep)
		usleep(500);
}




void ft_think(t_philo * philo)
{
	LOCK(philo->all->output_mtx);
	printf(AC_BLUE "%zu %d is thinking\n" RESET , current_time_in_milliseconds() - philo->all->curr_time, philo->index);
	UNLOCK(philo->all->output_mtx);
	ft_usleep((philo->all->t_die - (current_time_in_milliseconds() - philo->last_eat)) / 2);
}

void ft_eat (t_philo * philo)
{
    LOCK(philo->all->forks);
    LOCK(philo->all->forks);
    
    
    

    UNLOCK(philo->all->forks);
    UNLOCK(philo->all->forks);
}


void routine(t_philo *philo)
{
    while (1)
    {
        ft_eat(philo);
        ft_sleep(philo);
        ft_think(philo);
    }
}

size_t current_time_in_milliseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (((tv.tv_sec) * 1000) + ((tv.tv_usec) / 1000));
}


void ft_monitor(t_all *all)
{

    size_t i;

    i = 0;
    while (i < all->nbr_philos)
    {
        size_t val = current_time_in_milliseconds();
        if ((size_t)( val - all->philos[i].last_eat) > all->t_die)
		    {
                //declare death
                //clear data
                exit(1);
				return ;
			} 

        i = 0;
    }

}


int main(int ac, char *av)
{
    int nbr_philos = 5;
    sem_t *forks; 
    pid_t processes[nbr_philos];
    int m_pid;
    t_all all;

    size_t i = 0;
    m_pid = getpid();
    forks = sem_open("forks", O_CREAT, 0666, nbr_philos);
    if (!forks)
        exit(1);
    all.philos = malloc(sizeof(t_philo) * nbr_philos);
    while (i < nbr_philos)
    { 
        processes[i] = fork();
        if (processes[i] < 0)
        {
            //free all
            exit(1);
        }
        if (processes[i] == 0)
        {
            all.philos[i].index = i;
            all.philos[i].all = &all;
            all.philos[i].forks = forks;
            all.philos[i].last_eat = current_time_in_milliseconds();
            routine(&all.philos[i]);
        }
        else
        {

        }
        i++;
    }
    i = 0;
    ft_monitor(&all);

    return (0);
}