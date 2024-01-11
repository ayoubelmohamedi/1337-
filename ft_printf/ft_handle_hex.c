/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:47:04 by ael-moha          #+#    #+#             */
/*   Updated: 2023/12/22 13:47:19 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_handle_hex(unsigned int nbr, char x)
{
	int		c;
	char	res;
	char	*hexl;

	c = 0;
	hexl = NULL;
	if (x == 'x')
		hexl = "0123456789abcdef";
	else if (x == 'X')
		hexl = "0123456789ABCDEF";
	if (nbr / 16)
		c += ft_handle_hex(nbr / 16, x);
	res = hexl[(nbr % 16)];
	c += write(1, &res, 1);
	return (c);
}

int	ft_handle_hex2(unsigned long nbr)
{
	int	c;
	char	res;

	c = 0;
	if (nbr / 16)
		c += ft_handle_hex2(nbr / 16);
	res = "0123456789abcdef"[(nbr % 16)];
	c += write(1, &res, 1);
	return (c);
}
