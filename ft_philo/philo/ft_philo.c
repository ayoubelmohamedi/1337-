/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:13:08 by ael-moha          #+#    #+#             */
/*   Updated: 2024/11/05 21:17:18 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	*routine(void *args)
{
	t_philo	*philo;

	philo = ((t_philo *)args);
	if (philo->all->eat_count == 0)
		return (NULL);
	if (philo->index % 2 == 0) // prevent deadlock
		ft_usleep((philo->all->t_eat / 2));
	while (1)
	{
		if (!ft_check_simulation(philo))
			return (NULL);
		if (!ft_eat(philo))
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

int	ft_init_threads(t_all *all)
{
	size_t	i;

	i = 0;
	all->start_time = current_time_in_milliseconds();
	while (i < all->nbr_philos)
	{
		all->philos[i].last_eat = current_time_in_milliseconds();
		all->philos[i].is_done = 0;
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

int	init_all(t_all *all, int ac, char **av)
{
	size_t	i;

	pthread_mutex_init(all->output_mtx, NULL);
	pthread_mutex_init(all->meal_mtx, NULL);
	pthread_mutex_init(all->dead_lock, NULL);
	if (all->eat_count > 0)
		pthread_mutex_init(all->mutex_eat_counter, NULL);
	i = 0;
	while (i < all->nbr_philos)
	{
		all->philos[i].index = i + 1;
		pthread_mutex_init(&all->forks[i], NULL);
		if (i == all->nbr_philos - 1)
		{
			all->philos[i].r_fork = &all->forks[i];
			all->philos[i].my_fork = &all->forks[((i + 1) % all->nbr_philos)];
		}
		else
		{
			all->philos[i].my_fork = &all->forks[i];
			all->philos[i].r_fork = &all->forks[((i + 1) % all->nbr_philos)];
		}
		all->philos[i].all = all;
		i++;
	}
	return (0);
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

// 0 - if eat_count is zero, quit program [x]
// 1 - assign eat counter to each philo [x]
// 2- if one die, process should stop [x]
// 3 - check if all woks []
// 4 - free memory  and pthread_mutex_destroy before exit []

int	main(int ac, char **argv)
{
	int i;
	t_all all;

	if (!(is_valid(ac, argv)))
		return (1);
	ft_parse(&all, ac, argv);
	if (!malloc_data(&all))
		return (1);
	init_all(&all, ac, argv);
	ft_init_threads(&all);
	ft_monitor(&all);
	i = 0;
	while (i < all.nbr_philos)
		pthread_join(all.threads[i++], NULL);
	// ft_free_all(&all);
	return (0);
}