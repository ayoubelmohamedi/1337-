/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:43:37 by ael-moha          #+#    #+#             */
/*   Updated: 2024/11/23 19:58:12 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	ft_init_threads(t_all *all)
{
	int	i;

	i = 0;
	if (all->eat_count > 0)
		all->all_eat = 0;
	all->start_time = current_time_in_milliseconds();
	while (i < all->nbr_philos)
	{
		all->philos[i].last_eat = current_time_in_milliseconds();
		if (all->eat_count > 0)
			all->philos[i].meal = 0;
		else
			all->philos[i].meal = -1;
		if (pthread_create(&all->threads[i], NULL, routine, &all->philos[i]))
			return (0);
		i++;
	}
	return (1);
}

int	init_all(t_all *all)
{
	int	i;

	pthread_mutex_init(all->output_mtx, NULL);
	pthread_mutex_init(all->dead_lock, NULL);
	if (all->eat_count > 0)
		pthread_mutex_init(all->mutex_eat_counter, NULL);
	i = 0;
	while (i < all->nbr_philos)
	{
		all->philos[i].index = i + 1;
		pthread_mutex_init(&all->forks[i], NULL);
		pthread_mutex_init(&all->meal_mtx[i], NULL);
		if (i == all->nbr_philos - 1)
		{
			all->philos[i].r_fork = &all->forks[i];
			all->philos[i].my_fork = &all->forks[0];
		}
		else
		{
			all->philos[i].r_fork = &all->forks[((i + 1) % all->nbr_philos)];
			all->philos[i].my_fork = &all->forks[i];
		}
		all->philos[i++].all = all;
	}
	return (0);
}

void	ft_join_threads(t_all *all)
{
	int	j;

	j = 0;
	while (j < all->nbr_philos)
		pthread_join(all->threads[j++], NULL);
}