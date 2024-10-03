
#include "ft_philo.h"

void   ft_err_exit(t_philo * philo) 
{
    if (philo)
        free(philo);
    exit(1);
}

void ft_error(char c)
{
    //print error => parsing , memory allocatin, 
    if (c == 'p')
        printf("parsing error\n");
    if (c == 'm')
        printf("memory allocation failed\n");
}

int ft_check_simulation(t_philo *philo)
{
    int res;

    res = 1;
    LOCK(philo->all->dead_lock);
    if (!philo->all->simulation_running)
        res = 0;
    UNLOCK(philo->all->dead_lock);
    return (res);
}

void declare_death(t_philo *philo) {
	UNLOCK(philo->all->meal_mtx);
    LOCK(philo->all->dead_lock);
    LOCK(philo->all->output_mtx);
    printf("%zu %d died\n", current_time_in_milliseconds() - philo->last_eat, philo->index);
    UNLOCK(philo->all->output_mtx);
    philo->all->simulation_running = 0; 
    UNLOCK(philo->all->dead_lock);

    // unlock meal_mtx here
	// UNLOCK(philo->all->meal_mtx);   
   
}