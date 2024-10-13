
#include "ft_philo.h"

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
		res = (res * 10) + (nbr[i++] - '0');
	return (res * sign);
}

void ft_p_action(char m, t_philo *philo)
{
	LOCK(philo->all->output_mtx);
    if (m == 'e')
	    printf(AC_RED "%zu %d is eating\n" RESET, current_time_in_milliseconds() - philo->all->start_time, philo->index);
    else if (m == 's')
	    printf(AC_GREEN "%zu %d is sleeping\n" RESET, current_time_in_milliseconds() - philo->all->start_time, philo->index);
    else if (m == 't')
	    printf(AC_BLUE "%zu %d is thinking\n" RESET , current_time_in_milliseconds() - philo->all->start_time, philo->index);
    else if (m == 'd')
        printf("%zu %d died\n", current_time_in_milliseconds() - philo->all->start_time, philo->index);
    UNLOCK(philo->all->output_mtx);
}