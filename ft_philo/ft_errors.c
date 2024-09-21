

#include "ft_philo.h"


void   ft_err_exit(t_philo * philo) 
{
    if (philo)
        free(philo);
    exit(1);
}


void ft_exit(t_philo * philo)
{

    LOCK(philo->all->output_mtx);
    printf(AC_RED " %zu %d died\n" RESET, current_time_in_milliseconds() - philo->all->curr_time ,philo->index);
    exit(1);
    UNLOCK(philo->all->output_mtx);
}