/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:43:31 by ael-moha          #+#    #+#             */
/*   Updated: 2024/11/23 21:58:22 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	f_mtx(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	ft_free_all(t_all *all)
{
	ft_destroy_mutexes(all);
	f_mtx(all->threads);
	f_mtx(all->forks);
	f_mtx(all->philos);
	f_mtx(all->output_mtx);
	f_mtx(all->dead_lock);
	free(all->meal_mtx);	
	if (all->eat_count > 0)
		f_mtx(all->mutex_eat_counter);
}

void	ft_perror(char c)
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

int	ft_check_simulation(t_philo *philo)
{
	LOCK(philo->all->dead_lock);
	if (!philo->all->simulation_running)
		return (UNLOCK(philo->all->dead_lock), false);
	UNLOCK(philo->all->dead_lock);
	return (true);
}

void	declare_death(t_philo *philo)
{
	LOCK(philo->all->dead_lock);
		philo->all->simulation_running = 0;
	UNLOCK(philo->all->dead_lock);

	LOCK(philo->all->output_mtx);
	printf("%zu %d died\n", current_time_in_milliseconds()
		- philo->all->start_time, philo->index);
	UNLOCK(philo->all->output_mtx);
}