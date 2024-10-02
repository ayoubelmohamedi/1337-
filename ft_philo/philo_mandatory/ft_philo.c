
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

void* routine(void *args)
{
	t_philo *philo;

	philo = ((t_philo *) args);
	if (philo->index % 2 == 0) //prevent deadlock
		ft_usleep((philo->all->t_eat / 2));
	while (1)
	{	
		if (!ft_check_simulation(philo))
			return (NULL);
		ft_eat(philo);
		if (!ft_check_simulation(philo))
			return (NULL);
		ft_sleeping(philo);
		if (!ft_check_simulation(philo))
			return (NULL);
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
		all->philos[i].last_eat = current_time_in_milliseconds();
		if (pthread_create(&all->threads[i], NULL, routine, &all->philos[i]))
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
	all->simulation_running = 1;
	if(!av[5])
		all->eat_count = -1;
	else
		all->eat_count = ft_atoi(av[5]);
	size_t i = 0;
	pthread_mutex_init(all->output_mtx, NULL);
	pthread_mutex_init(all->meal_mtx, NULL);
	pthread_mutex_init(all->dead_lock, NULL);
	while (i < all->nbr_philos)
	{
		all->philos[i].index = i + 1;
		pthread_mutex_init(&all->forks[i], NULL);
		if (i == all->nbr_philos - 1)
		{
			all->philos[i].r_fork = &all->forks[i];
			all->philos[i].my_fork = &all->forks[((i + 1) % all->nbr_philos)] ;
		}
		else
		{
			all->philos[i].my_fork = &all->forks[i];
			all->philos[i].r_fork = &all->forks[((i + 1) % all->nbr_philos)] ;
		}
		all->philos[i].all = all;
		i++;
	}
	return (0);
}

void ft_monitor(t_all * all)
{
	if (!all)
		return ;
	int i;
	while (true)
	{
		i = 0;
		while (i < all->nbr_philos)
		{
			LOCK(all->meal_mtx);
			size_t val = current_time_in_milliseconds(); 	
			size_t l_eat = all->philos[i].last_eat; 
			if ((size_t)(val  - l_eat) > all->t_die)
			{
				declare_death(&all->philos[i]);
				return ;
			}
			UNLOCK(all->meal_mtx);
			i++;
		}
	}
}

int	main(int ac, char **argv)
{

	//todo : 1- stop philo when cycle of eating is reached
	// 2 - allocate mutexes in heap
	// 3- handle parsing 
	int i;
	t_all all;
	pthread_mutex_t forks[ft_atoi(argv[1])];
	pthread_t threads[ft_atoi(argv[1])];
	t_philo philos[ft_atoi(argv[1])];
	pthread_mutex_t output;
	pthread_mutex_t dead_lock;
	pthread_mutex_t meal_mtx;

	all.forks = forks;
	all.threads = threads;
	all.philos = philos;
	all.output_mtx = &output;
	all.meal_mtx = &meal_mtx; 
	all.dead_lock = &dead_lock;
	init_all(&all, ac, argv);
	ft_init_threads(&all);
	ft_monitor(&all);
	i = 0;
	while (i < all.nbr_philos)
		pthread_join(threads[i++], NULL);
	return (0);
}
