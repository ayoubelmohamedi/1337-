
#include "ft_philo_bonus.h"

// listen to child processes, exit all processes if one is death
void ft_monitor(t_all *all)
{
    size_t i;
    int status;

    i = 0;
    status = 0;
    while (i < all->nbr_philos)
    { 
        waitpid(-1, &status, 0);
        // either died or soemthing is off (segv)
        if (WEXITSTATUS(status) != 0)
        {
            i = 0;
            while (i < all->nbr_philos)
                kill(all->processes[i++], SIGTERM);
            return ;
        }
    }
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

void ft_agent(t_philo * philo)
{
    //check death in current process
    while (1)
    {
        LOCK(philo->all->meal_sem[philo->index]);
        size_t curr_t = current_time_in_milliseconds();
        size_t l_eat = philo->last_eat;
        if ((curr_t - l_eat) > philo->all->t_die)
        {
            declare_death(philo);
            return ;
        }
        UNLOCK(philo->all->meal_sem[philo->index]);
    }
}

sem_t *init_meal_sem(t_all *all)
{
    size_t i;
    sem_t *meal_sem;
    char *name;

    i  = -1;
    meal_sem = malloc(sizeof(sem_t) * all->nbr_philos);
    if (!meal_sem)
        return (0);
    all->meal_sem_names = philo_names(all->nbr_philos);
    while (++i < all->nbr_philos)
        meal_sem[i] = sem_open(all->meal_sem_names[i], 0666, 1);
    return (meal_sem);
}

int main(int ac, char *av)
{
    int nbr_philos = 5;
    sem_t *forks; 
    sem_t *output_sem;
    sem_t *meal_sem;
    pid_t processes[nbr_philos];
    pthread_t *threads;
    int m_pid;
    t_all all;

    size_t i = 0;
    m_pid = getpid();

    all.nbr_philos = nbr_philos;
    forks = sem_open("forks", O_CREAT, 0666, nbr_philos);
    output_sem = sem_open("output", O_CREAT, 0666, 1);
    meal_sem = init_meal_sem(&all);
    
    threads = malloc(sizeof(pthread_t) * nbr_philos);
    //free all in case of error
    if (!threads)
        return (1);
    all.forks = forks;
    all.output_sem = output_sem;
    all.meal_sem = meal_sem;
    if (!forks)
        exit(1);
    all.agents = malloc(sizeof(t_philo) * nbr_philos);
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
            if (pthread_create(all.agents[i], ft_agent, &all.philos[i]))
			    return (0); 
            // when to add pthread_join ?
            // maybe here >  > ? 
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