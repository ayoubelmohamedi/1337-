/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:48:24 by ael-moha          #+#    #+#             */
/*   Updated: 2023/12/24 20:21:33 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf.h"

int	ft_count(int nbr)
{
	int	c;

	c = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		c++;
	}
	if (nbr > 0)
	{
		c++;
		while (nbr / 10 > 0)
		{
			nbr /= 10;
			c++;
		}
	}
	return (c);
}

int	ft_handle_nbr(int n)
{
	int		size;
	char	c;
	int		nbr;

	nbr = n;
	c = 0;
	if (nbr == -2147483648)
	{
		write(1, "-2147483648", 11);
		c = 11;
		return (c);
	}
	size = ft_count(nbr);
	if (nbr < 0)
	{
		size--;
		nbr *= -1;
		write(1, "-", 1);
	}
	ft_printnbr(nbr, size);
	return (ft_count(n));
}

void	ft_printnbr(int nbr, int size)
{
	char	dec;

	while (size > 0)
	{
		dec = (nbr / (int)power(10, (size - 1))) % 10 + '0';
		write(1, &dec, 1);
		size--;
	}
}

int	power(int base, int pow)
{
	int	res;

	res = 1;
	if (pow == 0)
		return (1);
	if (pow == 1)
		return (base);
	while (pow > 0)
	{
		res *= base;
		pow--;
	}
	return (res);
}
