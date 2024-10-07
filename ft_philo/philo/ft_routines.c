
#include "ft_philo.h"


void ft_usleep(size_t time_to_sleep)
{
	size_t current = current_time_in_milliseconds();
	while (current_time_in_milliseconds() - current < time_to_sleep)
		usleep(500);
}

void ft_think(t_philo *philo) 
{
	LOCK(philo->all->output_mtx);
	printf(AC_BLUE "%zu %d is thinking\n" RESET , current_time_in_milliseconds() - philo->all->curr_time, philo->index);
	UNLOCK(philo->all->output_mtx);
	ft_usleep((philo->all->t_die - (current_time_in_milliseconds() - philo->last_eat)) / 2);
}

void ft_eat(t_philo *philo)
{
	LOCK(philo->my_fork);
	LOCK(philo->all->output_mtx);	
	printf(AC_YELLOW "%zu %d has taken a fork\n" RESET, current_time_in_milliseconds() - philo->all->curr_time, philo->index);
	UNLOCK(philo->all->output_mtx);	

	LOCK(philo->r_fork);
	LOCK(philo->all->output_mtx);	
	printf(AC_YELLOW "%zu %d has taken a fork\n" RESET, current_time_in_milliseconds() - philo->all->curr_time, philo->index);
	UNLOCK(philo->all->output_mtx);

	LOCK(philo->all->output_mtx);
	printf(AC_RED "%zu %d is eating\n" RESET, current_time_in_milliseconds() - philo->all->curr_time, philo->index);
	UNLOCK(philo->all->output_mtx);	
	LOCK(philo->all->meal_mtx);
	philo->last_eat = current_time_in_milliseconds();
	if (philo->meal_count >= 0)
		philo->meal_count++;
	UNLOCK(philo->all->meal_mtx);

	ft_usleep(philo->all->t_eat);
	UNLOCK(philo->my_fork);
	UNLOCK(philo->r_fork);
}

void ft_sleeping(t_philo *philo)
{
	LOCK(philo->all->output_mtx);
	printf(AC_GREEN "%zu %d is sleeping\n" RESET, current_time_in_milliseconds() - philo->all->curr_time, philo->index);
	UNLOCK(philo->all->output_mtx);
	ft_usleep(philo->all->t_sleep);
}
