/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:43:44 by ael-moha          #+#    #+#             */
/*   Updated: 2024/11/23 23:59:22 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	*routine(void *args)
{
	t_philo	*philo;

	philo = ((t_philo *)args);
	if (philo->all->eat_count == 0)
		return (NULL);
	if (philo->index % 2)
		ft_usleep(1, philo);
	while (1)
	{
		if (!ft_eat(philo))
			return (NULL);
		if (philo->all->eat_count > 0 && philo->meal == philo->all->eat_count)
		{
			LOCK(philo->all->mutex_eat_counter);
			philo->all->all_eat++;
			UNLOCK(philo->all->mutex_eat_counter);
			return (NULL);
		}
		ft_sleeping(philo);
		if (!ft_think(philo))
			return (NULL);
	}
	return (NULL);
}

bool	is_death(t_all *all, size_t i)
{
	LOCK(&all->meal_mtx[i]);
	if ((size_t)(current_time_in_milliseconds()
		- all->philos[i].last_eat) > (size_t)all->t_die)
	{
		declare_death(&all->philos[i]);
		UNLOCK(&all->meal_mtx[i]);
		return (true);
	}
	UNLOCK(&all->meal_mtx[i]);
	return (false);
}

void	ft_monitor(t_all *all)
{
	int	i;

	i = 0;
	while (true)
	{
		if (times_eat(all))
			break ;
		if (is_death(all, i))
			break ;
		i++;
		if (i >= (all->nbr_philos))
			i = 0;
		usleep(100);
	}
}

void	ft_parse(t_all *all, int ac, char **argv)
{
	all->nbr_philos = ft_atoi(argv[1]);
	all->t_die = ft_atoi(argv[2]);
	all->t_eat = ft_atoi(argv[3]);
	if (all->t_eat > all->t_die)
		all->t_eat = all->t_die;
	all->t_sleep = ft_atoi(argv[4]);
	if (all->t_sleep > all->t_die)
		all->t_sleep = all->t_die;
	if (ac == 6)
	{
		all->eat_count = ft_atoi(argv[5]);
		all->mutex_eat_counter = malloc(sizeof(pthread_mutex_t));
	}
	else
		all->eat_count = -1;
	all->simulation_running = 1;
}

int	main(int ac, char **argv)
{
	t_all	all;

	if (!(is_valid(ac, argv)))
		return (1);
	ft_parse(&all, ac, argv);
	if (!malloc_data(&all))
		return (1);
	init_all(&all);
	ft_init_threads(&all);
	ft_monitor(&all);
	ft_join_threads(&all);
	ft_free_all(&all);
	return (0);
}
