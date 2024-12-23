
#include "ft_philo_bonus.h"

// listen to child processes, exit all processes if one is death
void ft_monitor(t_all *all)
{
    size_t i;
    int status;
    int exit_status;

    i = 0;
    status = 0;
    while (i < all->nbr_philos)
    { 
        printf("monitoring process id %zu\n", i);
        waitpid(-1, &status, 0);
        // either died or something is off (segv)
        if (WIFEXITED(status))
        {
            exit_status = WEXITSTATUS(status); 
            if (exit_status > 1)
            {
                i = 0;
                while (i < all->nbr_philos)
                    kill(all->processes[i++], SIGTERM);
            }
            else
            {
                i = 0;
                while (i < all->nbr_philos)
                    kill(all->processes[i++], SIGTERM);
            }
            break;
        }
        i = 0;
    }
}

void routine(t_philo *philo)
{
    printf("Philo ==> %d created\n", philo->index);
    while (1)
    {
        printf("inside routine %d\n", philo->index);

        ft_eat(philo);
        ft_sleep(philo);
        ft_think(philo);
    }
}

void *ft_agent(void *parms)
{
    t_philo * philo;

    philo = (t_philo*) parms;
    //check death in current process
    while (1)
    {
        LOCK(philo->all->meal_sem[philo->index]);
        size_t curr_t = current_time_in_milliseconds();
        size_t l_eat = philo->last_eat;
        if ((curr_t - l_eat) > philo->all->t_die)
        {
            declare_death(philo);
            return (NULL);
        }
        UNLOCK(philo->all->meal_sem[philo->index]);
    }
    return (NULL);
}

sem_t **init_meal_sem(t_all *all)
{
    size_t i;
    sem_t **meal_sem;
    char *name;

    i  = -1;
    meal_sem = malloc(sizeof(sem_t*) * all->nbr_philos);
    if (!meal_sem)
        return (0);
    all->meal_sem_names = philo_names(all->nbr_philos);
    while (++i < all->nbr_philos)
        meal_sem[i] = sem_open(all->meal_sem_names[i], 0666, 1);
    return (meal_sem);
}

int malloc_data(t_all * all)
{
    all->forks = sem_open("forks", O_CREAT, 0666, all->nbr_philos);
    all->output_sem = sem_open("output", O_CREAT, 0666, 1);
    all->meal_sem = init_meal_sem(all);
    all->philos = malloc(sizeof(t_philo) * all->nbr_philos);
    all->agents = malloc(sizeof(pthread_t) * all->nbr_philos); 
    all->processes = malloc(sizeof(pid_t) * all->nbr_philos);
    //to check if malloc fails 

	return (1);
}

void ft_parse(t_all *all, int ac, char **argv)
{
	all->nbr_philos = ft_atoi(argv[1]);
	all->t_die = ft_atoi(argv[2]);
	all->t_eat = ft_atoi(argv[3]);
	all->t_sleep = ft_atoi(argv[4]);
	if (ac == 6)
		all->eat_count = ft_atoi(argv[5]);
	else
		all->eat_count = -1;
	all->simulation_running = 1;
}

// 1 - fix int first errors [x] 
// 2- format the file  [x]
// 3- handle parsing [x]
// 4- debugg []

int main(int ac, char **av)
{
    t_all all;

    size_t i = 0;
	if (!(is_valid(ac, av)))
		return (1);
    ft_parse(&all, ac, av);
    if(!malloc_data(&all))
        return (0);
    // if (ft_init_all(&all))
    //     return (0);
    while (i < all.nbr_philos)
    { 
        all.processes[i] = fork();
        if (all.processes[i] < 0)
        {
            //free all
            exit(1);
        }
        if (all.processes[i] == 0)
        {
            
            all.philos[i].index = i;
            all.philos[i].all = &all;
            all.philos[i].forks = all.forks;
            all.philos[i].last_eat = current_time_in_milliseconds();
            printf("process[%zu] => calling routine\n", i);
            routine(&all.philos[i]); 
            if (pthread_create(&all.agents[i], NULL, ft_agent, &all.philos[i]))
			    return (0);
            // when to add pthread_join ?
            // maybe here >  > ?  ans => each thread must be tighted up with their own process
            //2 - where to add   => pthread_detach(pthread_t thread) 
            // 3- when to use mutex attributes object
            pthread_join(all.agents[i],NULL);
        } 
        i++;
    }
    ft_monitor(&all); 
    return (0);
}