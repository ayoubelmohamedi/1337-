/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:13:06 by ael-moha          #+#    #+#             */
/*   Updated: 2024/11/06 17:51:45 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	ft_usleep(size_t time_to_sleep)
{
	size_t	current;

	current = current_time_in_milliseconds();
	while (current_time_in_milliseconds() - current < time_to_sleep)
		usleep(500);
}

void	ft_think(t_philo *philo)
{
	if (!ft_check_simulation(philo))
		return ;
	ft_usleep((philo->all->t_die - (current_time_in_milliseconds()
				- philo->last_eat)) / 2);
}

bool	ft_eat(t_philo *philo)
{
	LOCK(philo->my_fork);
	if (!ft_check_simulation(philo))
		return (UNLOCK(philo->my_fork), 0);
	LOCK(philo->all->output_mtx);
	printf(AC_YELLOW "%zu %d has taken a fork\n" RESET,
		current_time_in_milliseconds() - philo->all->start_time, philo->index);
	UNLOCK(philo->all->output_mtx);
	if (philo->all->nbr_philos == 1)
		return (UNLOCK(philo->my_fork), 0);
	LOCK(philo->r_fork);
	if (!ft_check_simulation(philo))
		return (UNLOCK(philo->r_fork), 0);
	LOCK(philo->all->output_mtx);
	printf(AC_YELLOW "%zu %d has taken a fork\n" RESET,
		current_time_in_milliseconds() - philo->all->start_time, philo->index);
	UNLOCK(philo->all->output_mtx);
	ft_p_action('e', philo);
	LOCK(philo->all->meal_mtx);
	philo->last_eat = current_time_in_milliseconds();
	UNLOCK(philo->all->meal_mtx);
	if (philo->meal >= 0)
		philo->meal++;
	ft_usleep(philo->all->t_eat);
	(UNLOCK(philo->r_fork), UNLOCK(philo->my_fork));
	return (1);
}

void	ft_sleeping(t_philo *philo)
{
	if (!ft_check_simulation(philo))
		return ;
	ft_p_action('s', philo);
	ft_usleep(philo->all->t_sleep);
}
