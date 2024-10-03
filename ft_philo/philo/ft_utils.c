
#include "ft_philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t current_time_in_milliseconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (((tv.tv_sec) * 1000) + ((tv.tv_usec) / 1000));
}

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

int	is_valid(int ac, char **args)
{
	if (!ft_is_nbr(args[1]) || !ft_is_nbr(args[2]) || !ft_is_nbr(args[3]))
		return (0);
	if (!ft_is_nbr(args[4]))
		return (0);
	// to check, the last item should be optional 
	if (ac == 5)
	{
		if (!ft_is_nbr(args[5]))
			return (0);
	}
	return (1);
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
		res = (res * 10) + (nbr[i++] - '0');
	return (res * sign);
}