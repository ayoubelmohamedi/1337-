
#include "ft_philo.h"

void	*routine(void *args)
{
	t_philo	*philo;

	philo = ((t_philo *)args);
	if (philo->all->eat_count == 0)
		return (NULL);
	if (philo->index % 2)
		ft_usleep((philo->all->t_eat / 2));
	while (1)
	{
		// if (!ft_check_simulation(philo))
		// 	return (NULL);
		if (!ft_eat(philo))
			return (NULL);
		// if (!ft_check_simulation(philo))
		// 	return (NULL);
		if (philo->all->eat_count > 0 && philo->meal == philo->all->eat_count)
		{
			LOCK(philo->all->mutex_eat_counter);
			philo->all->all_eat++;
			UNLOCK(philo->all->mutex_eat_counter);
			return (NULL);
		}
		ft_sleeping(philo);
		if(!ft_think(philo))
			return (NULL);
	}
	return (NULL);
}

// void	ft_monitor(t_all *all)
// {
// 	int		i;
// 	size_t	val;
// 	size_t	l_eat;

// 	if (all->eat_count == 0)
// 		return ;
// 	while (true)
// 	{
// 		i = 0;
// 		while (i < all->nbr_philos)
// 		{
// 			if (all->eat_count > 0)
// 			{
// 				LOCK(all->mutex_eat_counter);
// 				if (all->all_eat == all->nbr_philos)
// 					return (UNLOCK(all->mutex_eat_counter), (void)0);
// 				UNLOCK(all->mutex_eat_counter);
// 			}
// 			val = current_time_in_milliseconds();
// 			LOCK(all->meal_mtx);
// 			l_eat = all->philos[i].last_eat;
// 			UNLOCK(all->meal_mtx);
// 			if ((size_t)(val - l_eat) > all->t_die && (!all->philos[i].is_done))
// 				return (declare_death(&all->philos[i]), (void)0);
// 			i++;
// 		}
// 	}
// }

bool times_eat(t_all *all)
{
	if (all->eat_count > 0)
	{
		LOCK(all->mutex_eat_counter);
		if (all->all_eat >= all->nbr_philos)
		{
			LOCK(all->dead_lock);
			all->simulation_running = 0;
			UNLOCK(all->dead_lock);
 			return (UNLOCK(all->mutex_eat_counter), true);	
		}
		UNLOCK(all->mutex_eat_counter);	
	}
	return (false);	
}

bool is_death(t_all *all, size_t i)
{
	LOCK(&all->meal_mtx[i]);
	if ((size_t)(current_time_in_milliseconds() - all->philos[i].last_eat) >= (size_t)all->t_die)
	{
		declare_death(&all->philos[i]);
		UNLOCK(&all->meal_mtx[i]);
		return (true);	
	}
	UNLOCK(&all->meal_mtx[i]);
	return (false);
}

void ft_monitor(t_all *all)
{
	size_t i;

	i = 0;
	while (true)
	{
		if (times_eat(all))
			break;
		if (is_death(all, i))
			break;
		i++;
		if (i >= (all->nbr_philos))
			i = 0;
		usleep(100);
	}
}

int	malloc_data(t_all *all)
{
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	t_philo			*philos;
	pthread_mutex_t	*meal_mtx;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*output_mtx;

	forks = malloc(sizeof(pthread_mutex_t) * all->nbr_philos);
	threads = malloc(sizeof(pthread_t) * all->nbr_philos);
	philos = malloc(sizeof(t_philo) * all->nbr_philos);
	meal_mtx = malloc(sizeof(pthread_mutex_t) * all->nbr_philos);
	output_mtx = malloc(sizeof(pthread_mutex_t));
	dead_lock = malloc(sizeof(pthread_mutex_t));
	if (!forks || !threads || !philos || !output_mtx || !dead_lock)
	{
		(f_mtx(forks), f_mtx(threads), f_mtx(philos), f_mtx(output_mtx), f_mtx(dead_lock));
		return (0);
	}
	all->forks = forks;
	all->threads = threads;
	all->philos = philos;
	all->output_mtx = output_mtx;
	all->dead_lock = dead_lock;
	all->meal_mtx = meal_mtx;

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
