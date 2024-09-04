
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

void eat (t_philo * philo)
{
	if (philo->l_fork && philo->r_forl)
		usleep(philo->t_sleep);
}

void	*ft_perform_work(void *args)
{
	t_philo philo;
	
	philo = *((t_philo *) args);
	while (1)
	{
		eat(&philo);
		sleep(&philo);
		die(&philo);
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
		philos[i].index = i;
		philos[i].t_die = t_table->t_die;
		philos[i].t_eat = t_table->t_eat;
		philos[i].t_sleep = t_table->t_sleep;
		philos[i].nbr_philos = t_table->nbr_philos;
		philos[i++].fork = t_table->fork;
	}
	t_table->philos = philos;
	return (1);
}

int	main(int c, char **argv)
{
	int res;
	int i;
	pthread_mutex_t fork;

	if (c != 6 || !is_valid(argv))
		return (1);
	if (pthread_mutex_init(&fork, NULL))
		return (1);
	pthread_t threads[ft_atoi(argv[1])];
	t_all	t_table = {ft_atoi(argv[5]), ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]), &fork,NULL};
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
