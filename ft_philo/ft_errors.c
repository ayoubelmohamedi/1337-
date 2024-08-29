

#include "ft_philo.h"



void   ft_err_exit(t_philo * philos) 
{
    if (philos)
        free(philos);
    exit(1);
}
