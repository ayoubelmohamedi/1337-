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
#include "printf.h"

int	ft_handle_hex(int nbr, char x)
{
	static int	c;
	char		res;
	char		*hexl;

	c += 0;
	hexl = NULL;
	if (x == 'x')
		hexl = "0123456789abcdef";
	else if (x == 'X')
		hexl = "0123456789ABCDEF";
	if (nbr / 16)
		ft_handle_hex(nbr / 16, x);
	c++;
	res = hexl[(nbr % 16)];
	write(1, &res, 1);
	return (c);
}
