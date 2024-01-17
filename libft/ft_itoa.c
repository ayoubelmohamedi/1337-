/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 21:47:40 by ael-moha          #+#    #+#             */
/*   Updated: 2023/12/07 20:39:52 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static long	int_size(long nn)
{
	long	n;
	long	i;

	n = nn;
	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*res;
	long	size;
	long	nn;

	nn = (long)n;
	size = int_size(nn);
	res = (char *)malloc((size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '0';
	if (n < 0)
	{
		res[0] = '-';
		nn *= -1;
	}
	res[size] = '\0';
	size--;
	while (size >= 0)
	{
		if (res[0] == '-' && size == 0)
			return (res);
		res[size--] = (nn % 10) + '0';
		nn /= 10;
	}
	return (res);
}
