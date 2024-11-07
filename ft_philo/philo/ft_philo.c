/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:13:08 by ael-moha          #+#    #+#             */
/*   Updated: 2024/11/07 18:42:44 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	*routine(void *args)
{
	t_philo	*philo;

	philo = ((t_philo *)args);
	if (philo->all->eat_count == 0)
		return (NULL);
	if (philo->index % 2 == 0)
		ft_usleep((philo->all->t_eat / 2));
	while (1)
	{
		if (!ft_eat(philo))
			return (NULL);
		if (!ft_check_simulation(philo))
			return (NULL);
		if (philo->all->eat_count > 0 && philo->meal == philo->all->eat_count)
		{
			LOCK(philo->all->mutex_eat_counter);
			philo->all->all_eat++;
			philo->is_done = 1;
			UNLOCK(philo->all->mutex_eat_counter);
			return (NULL);
		}
		ft_sleeping(philo);
		ft_think(philo);
	}
	return (NULL);
}

void	ft_monitor(t_all *all)
{
	int		i;
	size_t	val;
	size_t	l_eat;

	if (all->eat_count == 0)
		return ;
	while (true)
	{
		i = 0;
		while (i < all->nbr_philos)
		{
			if (all->eat_count > 0)
			{
				LOCK(all->mutex_eat_counter);
				if (all->all_eat == all->nbr_philos)
					return (UNLOCK(all->mutex_eat_counter), (void)0);	
				UNLOCK(all->mutex_eat_counter);
			}
			val = current_time_in_milliseconds();
			l_eat = all->philos[i].last_eat;
			if ((size_t)(val - l_eat) > all->t_die && (!all->philos[i].is_done))
				return (declare_death(&all->philos[i]), (void)0);	
			i++;
		}
	}
}

int	malloc_data(t_all *all)
{
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	t_philo			*philos;
	pthread_mutex_t	*mutexes;

	forks = malloc(sizeof(pthread_mutex_t) * all->nbr_philos);
	threads = malloc(sizeof(pthread_t) * all->nbr_philos);
	philos = malloc(sizeof(t_philo) * all->nbr_philos);
	mutexes = malloc(sizeof(pthread_mutex_t) * 3);
	if (!forks || !threads || !philos || !mutexes)
	{
		(f_mtx(forks), f_mtx(threads), f_mtx(philos), f_mtx(mutexes));
		return (0);
	}
	all->forks = forks;
	all->threads = threads;
	all->philos = philos;
	all->mutexes = mutexes;
	all->output_mtx = &mutexes[0];
	all->meal_mtx = &mutexes[1];
	all->dead_lock = &mutexes[2];
	return (1);
}

void	ft_parse(t_all *all, int ac, char **argv)
{
	all->nbr_philos = ft_atoi(argv[1]);
	all->t_die = ft_atoi(argv[2]);
	all->t_eat = ft_atoi(argv[3]);
	all->t_sleep = ft_atoi(argv[4]);
	if (ac == 6)
	{
		all->eat_count = ft_atoi(argv[5]);
		all->mutex_eat_counter = malloc(sizeof(pthread_mutex_t));
	}
	else
		all->eat_count = -1;
	all->simulation_running = 1;
}


//TODO : add mutex_destroy 

int	main(int ac, char **argv)
{
	t_all	all;

	if (!(is_valid(ac, argv)))
		return (1);
	ft_parse(&all, ac, argv);
	if (!malloc_data(&all))
		return (1);
	init_all(&all, ac, argv);
	ft_init_threads(&all);
	ft_monitor(&all);
	ft_join_threads(&all);
	ft_free_all(&all);
	return (0);
}
