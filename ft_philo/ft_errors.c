
#include "ft_philo.h"

void   ft_err_exit(t_philo * philo) 
{
    if (philo)
        free(philo);
    exit(1);
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
    LOCK(philo->all->dead_lock);
    philo->all->simulation_running = 0; 
    UNLOCK(philo->all->dead_lock);

    // unlock meal_mtx here
	// UNLOCK(philo->all->meal_mtx);   
    LOCK(philo->all->output_mtx);
    printf("%zu %d died\n", current_time_in_milliseconds() - philo->last_eat, philo->index);
    UNLOCK(philo->all->output_mtx);
}