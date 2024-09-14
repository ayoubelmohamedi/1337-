
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
    return (size_t)(tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
}

size_t left(t_philo philo) 
{  
    // number of the left neighbor of philosopher i, for whom both forks are available
    return (philo.index - 1 + philo.table->nbr_philos) % philo.table->nbr_philos; // N is added for the case when  i - 1 is negative
}

size_t right(t_philo philo) 
{  
    // number of the right neighbor of the philosopher i, for whom both forks are available
    return (philo.index + 1) % philo.table->nbr_philos;
}

void ft_usleep(size_t time_to_sleep)
{
	usleep(time_to_sleep * 1000); 
}

void ft_think(t_philo philo) 
{
    LOCK(philo.table->output_mtx);  // critical section for uninterrupted print
	printf(AC_BLUE "%zu %d is thinking\n" RESET , current_time_in_milliseconds() - philo.table->curr_time, philo.index);
    UNLOCK(philo.table->output_mtx);
}

void ft_eat(t_philo philo)
{
	LOCK(philo.table->output_mtx);
	printf(AC_YELLOW "\t%zu %d is eating\n" RESET, current_time_in_milliseconds() - philo.table->curr_time, philo.index);
	UNLOCK(philo.table->output_mtx);
	ft_usleep(philo.t_eat);
}

void ft_sleeping(t_philo philo)
{
	LOCK(philo.table->output_mtx);
	printf(AC_GREEN "%zu %d is sleeping\n" RESET, current_time_in_milliseconds() - philo.table->curr_time, philo.index);
	UNLOCK(philo.table->output_mtx);
	ft_usleep(philo.t_sleep);
}

void ft_takeforks(t_philo philo)
{
	LOCK(&philo.table->forks[philo.index]);
	LOCK(philo.table->output_mtx);
	printf("%zu %d has taken his fork\n", current_time_in_milliseconds() - philo.table->curr_time, philo.index);	
	UNLOCK(philo.table->output_mtx);

	
	LOCK(&philo.table->forks[left(philo)]);
	LOCK(philo.table->output_mtx);
	printf("%zu %d has taken left fork\n", current_time_in_milliseconds() - philo.table->curr_time, philo.index);
	UNLOCK(philo.table->output_mtx);
	ft_eat(philo);

	UNLOCK(&philo.table->forks[philo.index]);
	UNLOCK(&philo.table->forks[left(philo)]);
}


void* ft_perform_work(void *args)
{
	t_philo philo;

	philo = *((t_philo *) args);
	if (philo.index % 2 == 0)
		ft_usleep(100);
	while (1)
	{
		ft_takeforks(philo);
		ft_sleeping(philo);
		ft_think(philo);
	}
	return (NULL);
}

int	ft_init_threads(pthread_t *threads, t_all *table)
{
	size_t i;
	int res;

	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_create(&threads[i], NULL, ft_perform_work, &table->philos[i]))
			return (0); 
		i++;
	}
	return (1);
}

int ft_init_philos(t_all * t_table)
{
	t_philo * philos;
	size_t	i;

	philos = malloc(sizeof(t_philo) * t_table->nbr_philos);
	if (!philos)
		return (0);
	i  = 0;
	while (i < t_table->nbr_philos)
	{
		philos[i].index = i + 1;
		philos[i].t_die = t_table->t_die;
		philos[i].t_eat = t_table->t_eat;
		philos[i].t_sleep = t_table->t_sleep;
		philos[i].is_dead = 0;
		philos[i++].table = t_table;
	}
	t_table->philos = philos;
	return (1);
}

int	main(int c, char **argv)
{
	int res;
	int i;
	pthread_mutex_t output_mtx;
	pthread_mutex_t critical_region;

	// if (c != 5 || !is_valid(argv))
	// 	return (1);
	pthread_mutex_t both_forks_available[ft_atoi(argv[1])];
	State state[ft_atoi(argv[1])];
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&both_forks_available[i],NULL);
		state[i++] = THINKING;
	} 
	pthread_t threads[ft_atoi(argv[1])];
	pthread_mutex_init(&output_mtx, NULL);
	pthread_mutex_init(&critical_region, NULL);
	t_all	t_table = {ft_atoi(argv[4]), ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]), current_time_in_milliseconds(),state, both_forks_available, &critical_region, &output_mtx, NULL};
	if (!ft_init_philos(&t_table))
		return (1);
	if (!ft_init_threads(threads ,&t_table))
		ft_err_exit(t_table.philos);
	i = 0;
	while (i < t_table.nbr_philos)
	{
		if (pthread_join(threads[i],NULL))
			ft_err_exit(t_table.philos);
		i++;
	}
	return (0);
}
