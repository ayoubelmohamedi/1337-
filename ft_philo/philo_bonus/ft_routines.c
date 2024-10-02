


#include "ft_philo_bonus.h"


void ft_usleep(size_t time_to_sleep)
{
	size_t current = current_time_in_milliseconds();
	while (current_time_in_milliseconds() - current < time_to_sleep)
		usleep(500);
}

void ft_think(t_philo * philo)
{
	LOCK(philo->all->output_sem);
	printf(AC_BLUE "%zu %d is thinking\n" RESET , current_time_in_milliseconds() - philo->all->curr_time, philo->index);
	UNLOCK(philo->all->output_sem);
	ft_usleep((philo->all->t_die - (current_time_in_milliseconds() - philo->last_eat)) / 2);
}

void ft_sleep(t_philo *philo)
{
	LOCK(philo->all->output_sem);
	printf(AC_BLUE "%zu %d is sleeping\n" RESET , current_time_in_milliseconds() - philo->all->curr_time, philo->index);
	UNLOCK(philo->all->output_sem);
    
    ft_usleep(philo->all->t_sleep);
}

void ft_eat (t_philo * philo)
{
    LOCK(philo->all->forks);
    LOCK(philo->all->output_sem);
	printf(AC_YELLOW "%zu %d has taken a fork\n" RESET, current_time_in_milliseconds() - philo->all->curr_time, philo->index);
    UNLOCK(philo->all->output_sem);

    LOCK(philo->all->forks);
    LOCK(philo->all->output_sem);
	printf(AC_YELLOW "%zu %d has taken a fork\n" RESET, current_time_in_milliseconds() - philo->all->curr_time, philo->index);
    UNLOCK(philo->all->output_sem);

    LOCK(philo->all->output_sem);
	printf(AC_RED "%zu %d is eating\n" RESET, current_time_in_milliseconds() - philo->all->curr_time, philo->index);
    UNLOCK(philo->all->output_sem); 

    LOCK(philo->all->meal_sem);
    philo->last_eat = current_time_in_milliseconds(); 
    UNLOCK(philo->all->meal_sem);
    ft_usleep(philo->all->t_eat); 
    UNLOCK(philo->all->forks);
    UNLOCK(philo->all->forks);
}