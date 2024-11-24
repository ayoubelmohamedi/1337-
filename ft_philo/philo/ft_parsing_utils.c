/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:43:37 by ael-moha          #+#    #+#             */
/*   Updated: 2024/11/24 00:01:10 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	malloc_data2(t_all *all)
{
	pthread_mutex_t	*meal_mtx;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*output_mtx;

	meal_mtx = malloc(sizeof(pthread_mutex_t) * all->nbr_philos);
	output_mtx = malloc(sizeof(pthread_mutex_t));
	dead_lock = malloc(sizeof(pthread_mutex_t));
	if (!meal_mtx || !output_mtx || !dead_lock)
		return (f_mtx(output_mtx), f_mtx(dead_lock), f_mtx(meal_mtx), 0);
	all->output_mtx = output_mtx;
	all->dead_lock = dead_lock;
	all->meal_mtx = meal_mtx;
	return (1);
}

int	malloc_data(t_all *all)
{
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	t_philo			*philos;

	if (!malloc_data2(all))
		return (0);
	forks = malloc(sizeof(pthread_mutex_t) * all->nbr_philos);
	threads = malloc(sizeof(pthread_t) * all->nbr_philos);
	philos = malloc(sizeof(t_philo) * all->nbr_philos);
	if (!forks || !threads || !philos)
		return (f_mtx(forks), f_mtx(threads), f_mtx(philos), 0);
	all->forks = forks;
	all->threads = threads;
	all->philos = philos;
	return (1);
}

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
