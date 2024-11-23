#include "ft_philo.h"

void	f_mtx(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	ft_free_all(t_all *all)
{
	ft_destroy_mutexes(all);
	free(all->forks);
	free(all->threads);
	free(all->philos);
	free(all->output_mtx);
	free(all->meal_mtx);
	if (all->eat_count > 0)
		free(all->mutex_eat_counter);
}

void	ft_perror(char c)
{
	if (c == 'p')
		printf("parsing error\n");
	if (c == 'm')
		printf("memory allocation failed\n");
	if (c == 'z')
		printf("nbr of philos is 0\n");
	if (c == 'c')
		printf("parsing error: check nbr of arguments\n");
}

int	ft_check_simulation(t_philo *philo)
{
	int	res;

	res = 1;
	LOCK(philo->all->dead_lock);
	if (!philo->all->simulation_running)
		res = 0;
	UNLOCK(philo->all->dead_lock);
	return (res);
}

void	declare_death(t_philo *philo)
{
	LOCK(philo->all->dead_lock);
	ft_p_action('d', philo);
	philo->all->simulation_running = 0;
	UNLOCK(philo->all->dead_lock);
}