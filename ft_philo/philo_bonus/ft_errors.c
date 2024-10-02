

#include "ft_philo_bonus.h"


void declare_death(t_philo * philo)
{
    UNLOCK(philo->all->meal_sem[philo->index]);
    LOCK(philo->all->output_sem);
    printf("%zu %d died\n", current_time_in_milliseconds() - philo->last_eat, philo->index);
    UNLOCK(philo->all->output_sem);
    exit(1);
}