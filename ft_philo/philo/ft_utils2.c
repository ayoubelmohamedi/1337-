/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:12:55 by ael-moha          #+#    #+#             */
/*   Updated: 2024/11/23 22:00:51 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	ft_destroy_mutexes(t_all *all)
{
	int	i;

	i = -1;
	while (i++ < all->nbr_philos)
	{	
		pthread_mutex_destroy(&all->forks[i]);
		pthread_mutex_destroy(&all->meal_mtx[i]);	
	}
	if (all->eat_count > 0)
		pthread_mutex_destroy(all->mutex_eat_counter);
	pthread_mutex_destroy(all->dead_lock);
	pthread_mutex_destroy(all->output_mtx);
}

int	ft_atoi(const char *nbr)
{
	int			sign;
	int			i;
	long long	res;

	sign = 1;
	res = 0;
	i = 0;
	if (nbr == NULL)
		return (0);
	while (nbr[i] == '\t' || nbr[i] == '\n' || nbr[i] == '\v' || nbr[i] == '\f'
		|| nbr[i] == '\r' || nbr[i] == ' ')
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		res = (res * 10) + (nbr[i++] - '0');
		if (res > INT_MAX || res < INT_MIN)	
			return (-1);
	}
	return (res * sign);
}

bool	ft_p_action(char m, t_philo *philo)
{
	LOCK(philo->all->output_mtx);
	if (!ft_check_simulation(philo))
		return (UNLOCK(philo->all->output_mtx), false);
	if (m == 'e')
		printf(AC_RED "%zu %d is eating\n" RESET, current_time_in_milliseconds()
			- philo->all->start_time, philo->index);
	else if (m == 's')
		printf(AC_GREEN "%zu %d is sleeping\n" RESET,
			current_time_in_milliseconds() - philo->all->start_time,
			philo->index);
	else if (m == 't')
		printf(AC_BLUE "%zu %d is thinking\n" RESET,
			current_time_in_milliseconds() - philo->all->start_time,
			philo->index);
	UNLOCK(philo->all->output_mtx);
	return (true);
}
