
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


void ft_eat(t_philo philo)
{
	LOCK(philo.table->output_mtx);
	printf("%zu %d is eating\n", current_time_in_milliseconds() - philo.table->curr_time, philo.index);
	UNLOCK(philo.table->output_mtx);
	ft_usleep(philo.t_eat);
}

void ft_sleeping(t_philo philo)
{
	LOCK(philo.table->output_mtx);
	printf("%zu %d is sleeping\n", current_time_in_milliseconds() - philo.table->curr_time, philo.index);
	UNLOCK(philo.table->output_mtx);
	ft_usleep(philo.t_sleep);
}

void test(t_philo philo)
{
	if (philo.table->state[philo.index] == HUNGRY
		&& philo.table->state[left(philo)] != EATING && philo.table->state[right(philo)] != EATING)
		{
			LOCK(&philo.table->forks[philo.index]);
			philo.table->state[philo.index] = EATING;
			LOCK(philo.table->output_mtx);
			printf("%zu %d has taken a fork\n", current_time_in_milliseconds() - philo.table->curr_time, philo.index);
			printf("%zu %d has taken a fork\n", current_time_in_milliseconds() - philo.table->curr_time, philo.index);
			UNLOCK(philo.table->output_mtx);
			UNLOCK(&philo.table->forks[philo.index]);
			// alternative with semaphores 
			// both_forks_available[i].release();
		}
}

void ft_takeforks(t_philo philo)
{
	LOCK(philo.table->critical_region);
	philo.table->state[philo.index] = HUNGRY;
	LOCK(philo.table->output_mtx);
	printf("%zu %d is thinking\n", current_time_in_milliseconds() - philo.table->curr_time, philo.index);
	UNLOCK(philo.table->output_mtx);
	test(philo);
	UNLOCK(philo.table->critical_region);
}

void ft_putforks(t_philo philo)
{
	LOCK(philo.table->critical_region);
	philo.table->state[philo.index] = THINKING;
	test(philo.table->philos[left(philo)]);
	test(philo.table->philos[right(philo)]);
	UNLOCK(philo.table->critical_region);	
}

void	*ft_perform_work(void *args)
{
	t_philo philo;
	
	philo = *((t_philo *) args);
	while (1)
	{
		ft_takeforks(philo);
		ft_eat(philo);
		ft_putforks(philo);
		ft_sleeping(philo);
	}
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
		philos[i].index = i;
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
	pthread_mutex_t forks[ft_atoi(argv[1])];
	State state[ft_atoi(argv[1])];
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&forks[i],NULL);
		state[i++] = THINKING;
	} 
	pthread_t threads[ft_atoi(argv[1])];
	pthread_mutex_init(&output_mtx, NULL);
	pthread_mutex_init(&critical_region, NULL);
	t_all	t_table = {ft_atoi(argv[4]), ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]), current_time_in_milliseconds(),state, forks, &critical_region, &output_mtx, NULL};
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
