
#include "ft_philo.h"

void	ft_usleep(size_t time_to_sleep)
{
	size_t	current;

	current = current_time_in_milliseconds();
	while (current_time_in_milliseconds() - current < time_to_sleep)
		usleep(100);
}

int	ft_think(t_philo *philo)
{
	if (ft_check_simulation(philo))
	{
		ft_p_action('t',philo);
		ft_usleep((philo->all->t_die - (current_time_in_milliseconds()
				- philo->last_eat)) / 2);
		return (1);
	}
	return (0);
}

void ft_take_forks(t_philo *philo)
{
	if (philo->index % 2 == 0) {
		LOCK(philo->my_fork);
		LOCK(philo->r_fork);
		LOCK(philo->all->output_mtx);
		printf(AC_YELLOW "%zu %d has taken a fork\n%zu %d has taken a fork\n" RESET,
			current_time_in_milliseconds() - philo->all->start_time, philo->index,
			current_time_in_milliseconds() - philo->all->start_time, philo->index);
		UNLOCK(philo->all->output_mtx);
	} else {
		LOCK(philo->r_fork);
		LOCK(philo->my_fork);
		LOCK(philo->all->output_mtx);
		printf(AC_YELLOW "%zu %d has taken a fork\n%zu %d has taken a fork\n" RESET,
			current_time_in_milliseconds() - philo->all->start_time, philo->index,
			current_time_in_milliseconds() - philo->all->start_time, philo->index);
		UNLOCK(philo->all->output_mtx);
	}
}

bool	ft_eat(t_philo *philo)
{	
	// if (philo->all->nbr_philos == 1)
	// 	return (UNLOCK(philo->my_fork), 0);	
	if (!ft_check_simulation(philo))
		return (0);
	ft_take_forks(philo);	
	ft_p_action('e', philo);
	LOCK(&philo->all->meal_mtx[philo->index - 1]);
	philo->last_eat = current_time_in_milliseconds();
	UNLOCK(&philo->all->meal_mtx[philo->index - 1]);
	if (philo->meal >= 0)
		philo->meal++;
	if (!ft_check_simulation(philo))
		return (UNLOCK(philo->r_fork), UNLOCK(philo->my_fork), 0);
	ft_usleep(philo->all->t_eat);
	(UNLOCK(philo->r_fork), UNLOCK(philo->my_fork));
	return (1);
}

void		ft_sleeping(t_philo *philo)
{
	if (ft_check_simulation(philo))
	{
		ft_p_action('s', philo);
		ft_usleep(philo->all->t_sleep);	
	}
}