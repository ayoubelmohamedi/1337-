
#include "ft_philo_bonus.h"


size_t left(t_philo *philo) 
{  
    // number of the left neighbor of philosopher i, for whom both forks are available
    return (philo->index - 1 + philo->all->nbr_philos) % philo->all->nbr_philos; // N is added for the case when  i - 1 is negative
}

size_t right(t_philo *philo) 
{  
    // number of the right neighbor of the philosopher i, for whom both forks are available
    return (philo->index + 1) % philo->all->nbr_philos;
}

void ft_usleep(size_t time_to_sleep)
{
	size_t current = current_time_in_milliseconds();
	while (current_time_in_milliseconds() - current < time_to_sleep)
		usleep(500);
}

void ft_think(int i, t_all * all)
{
	LOCK(philo->all->output_mtx);
	printf(AC_BLUE "%zu %d is thinking\n" RESET , current_time_in_milliseconds() - philo->all->curr_time, philo->index);
	UNLOCK(philo->all->output_mtx);
	ft_usleep((philo->all->t_die - (current_time_in_milliseconds() - philo->last_eat)) / 2);
}

void ft_test(int process_nbr, t_all *all)
{
    if (all->philos[process_nbr].state == HUNGRY && all->philos[process_nbr].state != EATING
        && all->philos[process_nbr].state != EATING)
        {
           all->philos[process_nbr].state = EATING;
           
        }
}

void ft_take_forks(int i, t_all *all)
{

}

void routine(int process_nbr, t_all *all)
{
    printf("current pid => %d\n", process_nbr);

    while (1)
    {
        ft_take_forks(process_nbr, all);
        ft_eat(process_nbr, all);
        ft_put_forks(process_nbr, all);
        ft_sleep(process_nbr, all);
        ft_think(process_nbr, all);
    }
}

int main(int ac, char *av)
{

    int nbr_philos = 5;
    sem_t forks[nbr_philos]; 
    int processes[nbr_philos];
    int m_pid;
    t_all all;

    size_t i = 0;
    m_pid = getpid();
    while (i < nbr_philos)
    {
        processes[i] = fork();
        if (sem_init(&forks[i], 0, 0) != 0)
        {
            perror("Failed to initialize semaphore\n");
            exit(1);
        }
        i++;
    }
    i = 0;
    while (i < nbr_philos)
    {
        routine(i++, &all);
    }

    ft_monitor(all);
    while (i < nbr_philos)
        sem_destroy(&forks[i++]); 

    return (0);
}