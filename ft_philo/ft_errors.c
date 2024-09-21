

#include "ft_philo.h"


void   ft_err_exit(t_philo * philo) 
{
    if (philo)
        free(philo);
    exit(1);
}


void declare_death(t_philo *philo) {
    LOCK(philo->all->dead_lock);
    if (philo->all->simulation_running) 
    {
        philo->all->simulation_running = 0; 
        printf("%zu %d died\n", current_time_in_milliseconds() - philo->last_eat, philo->index);
    }
    UNLOCK(philo->all->dead_lock);
}