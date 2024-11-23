/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:43:55 by ael-moha          #+#    #+#             */
/*   Updated: 2024/11/23 19:43:56 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void ft_usleep(size_t time_to_sleep, t_philo *philo)
{
    size_t current;

    current = current_time_in_milliseconds();
    while (current_time_in_milliseconds() - current < time_to_sleep)
    {
        if (!ft_check_simulation(philo))
            return ;
        usleep(500);
    }
}

int	ft_think(t_philo *philo)
{
		if (!ft_p_action('t',philo))
			return (false);
		ft_usleep((philo->all->t_die - (current_time_in_milliseconds() - philo->last_eat)) / 2, philo);
		return(true);
}

bool  ft_take_forks(t_philo *philo)
{
	if (!ft_check_simulation(philo))
		return (false);
	LOCK(philo->my_fork);
	if (!ft_check_simulation(philo))
		return (UNLOCK(philo->my_fork), false);
	LOCK(philo->r_fork);
	LOCK(philo->all->output_mtx);
	if (!ft_check_simulation(philo))
		return (UNLOCK(philo->my_fork),UNLOCK(philo->r_fork),UNLOCK(philo->all->output_mtx), false);
	printf(AC_YELLOW "%zu %d has taken a fork\n%zu %d has taken a fork\n" RESET,
		current_time_in_milliseconds() - philo->all->start_time, philo->index,
		current_time_in_milliseconds() - philo->all->start_time, philo->index);
	UNLOCK(philo->all->output_mtx);
	return (true);
}

bool	ft_eat(t_philo *philo)
{	
	if (!ft_take_forks(philo))
		return (false);
	if (!ft_p_action('e', philo))
		return (UNLOCK(philo->my_fork), UNLOCK(philo->r_fork), false);
	LOCK(&philo->all->meal_mtx[philo->index - 1]);
	philo->last_eat = current_time_in_milliseconds();
	UNLOCK(&philo->all->meal_mtx[philo->index - 1]);
	if (philo->meal >= 0)
		philo->meal++;
	ft_usleep(philo->all->t_eat, philo);
	(UNLOCK(philo->my_fork), UNLOCK(philo->r_fork));
	return (1);
}

void		ft_sleeping(t_philo *philo)
{
	ft_p_action('s', philo);
	ft_usleep(philo->all->t_sleep, philo);
}