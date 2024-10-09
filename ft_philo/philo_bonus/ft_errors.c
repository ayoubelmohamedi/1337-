

#include "ft_philo_bonus.h"

void ft_perror(char c)
{
    if (c == 'p')
        printf("parsing error\n");
    if (c == 'm')
        printf("memory allocation failed\n");
    if (c == 'z')
        printf("nbr of philos is 0\n");
    if (c == 'c')
        printf("parsing error: check nbr of arguments\n");
}

void declare_death(t_philo * philo)
{
    UNLOCK(philo->all->meal_sem[philo->index]);
    LOCK(philo->all->output_sem);
    printf("%zu %d died\n", current_time_in_milliseconds() - philo->last_eat, philo->index);
    UNLOCK(philo->all->output_sem);
    exit(1);
}
