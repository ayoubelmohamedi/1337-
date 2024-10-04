
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

int ft_check_max_zero(int ac, char **args)
{
	if (ac > 5 || ac <= 1)
	{
		ft_perror('c');
		return (1);
	}
	if (ac > 4 && ft_is_nbr(args[1]) && ft_atoi(args[1]) == 0) 
	{
		ft_perror('z');
		return (1);
	}
	return (0);
}

int	is_valid(int ac, char **args)
{
	size_t i;

	i = 1;
	if (ft_check_max_zero(ac, args))
		return (0);
	while (i < 4)
	{
		if (!ft_is_nbr(args[i]) || ft_atoi(args[i]) < 0)
		{
			ft_perror('p');
			return (0);
		}
		i++;
	}
	if (ac == 5)
	{
		if (!ft_is_nbr(args[5]) && ft_atoi(args[5]) < 0)
		{
			ft_perror('p');
			return (0);
		}
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