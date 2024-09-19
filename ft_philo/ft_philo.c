
#include "ft_philo.h"

int	ft_is_nbr(char *nbr)
{
	size_t	i;

	i = 0;
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i++]))
			return (0);
	}
	return (1);
}

int	is_valid(char **args)
{
	if (!ft_is_nbr(args[1]) || !ft_is_nbr(args[2]) || !ft_is_nbr(args[3]))
		return (0);
	if (!ft_is_nbr(args[4]) || !ft_is_nbr(args[5]))
		return (0);
	return (1);
}

size_t current_time_in_milliseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (((tv.tv_sec) * 1000) + ((tv.tv_usec) / 1000));
}

void ft_usleep(size_t time_to_sleep)
{
	size_t current = current_time_in_milliseconds();
	while (current_time_in_milliseconds() - current < time_to_sleep)
		usleep(500);
}

void ft_think(t_philo *philo) 
{
	LOCK(philo->all->output_mtx);
	printf(AC_BLUE "%zu\t%d is thinking\n" RESET , current_time_in_milliseconds() - philo->all->curr_time, philo->index);
	UNLOCK(philo->all->output_mtx);
}


void ft_eat(t_philo *philo)
{
	LOCK(philo->my_fork);
	printf(AC_YELLOW "%zu\t%d takes a fork\n" RESET, current_time_in_milliseconds() - philo->all->curr_time, philo->index);
	LOCK(philo->r_fork);
	printf(AC_YELLOW "%zu\t%d takes a fork\n" RESET, current_time_in_milliseconds() - philo->all->curr_time, philo->index);

	LOCK(philo->all->output_mtx);
	printf(AC_YELLOW "%zu\t%d is eating\n" RESET, current_time_in_milliseconds() - philo->all->curr_time, philo->index);
	UNLOCK(philo->all->output_mtx);	

	ft_usleep(philo->all->t_eat);
	philo->last_eat = current_time_in_milliseconds();
	UNLOCK(philo->r_fork);
	UNLOCK(philo->my_fork);
}

void ft_sleeping(t_philo *philo)
{
	LOCK(philo->all->output_mtx);
	printf(AC_GREEN "%zu\t%d is sleeping\n" RESET, current_time_in_milliseconds() - philo->all->curr_time, philo->index);
	UNLOCK(philo->all->output_mtx);
	ft_usleep(philo->all->t_sleep);
}

void* routine(void *args)
{
	t_philo *philo;

	philo = ((t_philo *) args);
	if (philo->index % 2 == 0)//prevent deadlock
		ft_usleep((philo->all->t_eat / 2));
	while (1)
	{
		ft_eat(philo);
		ft_sleeping(philo);
		ft_think(philo);
	}
	return (NULL);
}

int	ft_init_threads(t_all *all)
{
	size_t i;

	i = 0;
	all->curr_time = current_time_in_milliseconds();
	while (i < all->nbr_philos)
	{
		if (pthread_create(all->threads + i, NULL, routine, all->philos + i))
			return (0); 
		i++;
	}
	return (1);
}

int init_all(t_all *all, int ac, char **av)
{
	all->ac = ac;
	all->av = av;
	all->nbr_philos =  ft_atoi(av[1]);
	all->t_die = ft_atoi(av[2]);
	all->t_eat = ft_atoi(av[3]);
	all->t_sleep =  ft_atoi(av[4]);
	if(!av[5])
		all->eat_count = -1;
	else
		all->eat_count = ft_atoi(av[5]);
	size_t i = 0;
	while (i < all->nbr_philos)
	{
		all->philos[i].index = i + 1;
		pthread_mutex_init(all->forks + i, NULL);
		all->philos[i].my_fork = all->forks + i;
		all->philos[i].r_fork = all->forks + ((i + 1) % all->nbr_philos);
		all->philos[i].all = all;
		i++;
	}
	return (0);
}


void ft_monitor(t_all * all)
{
	// if (!all)
	// 	return ;
	int i = 0;
	while (true)
	{
		// while (all->philos[i])	
	}
}

int	main(int ac, char **argv)
{

	int i;
	t_all all;
	pthread_mutex_t forks[ft_atoi(argv[1])];
	pthread_t threads[ft_atoi(argv[1])];
	t_philo philos[ft_atoi(argv[1])];

	all.forks = forks;
	all.threads = threads;
	all.philos = philos;
	init_all(&all, ac, argv);
	ft_init_threads(&all);
	ft_monitor(&all);
	i = 0;
	while (i < all.nbr_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}
