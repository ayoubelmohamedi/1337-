/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_usign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:47:53 by ael-moha          #+#    #+#             */
/*   Updated: 2023/12/22 13:48:05 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_handle_usign(unsigned int nbr)
{
	char	deg;
	int		c;
	
	c = 0;
	if (nbr / 10)
		c += ft_handle_usign(nbr / 10);
	deg = (nbr % 10) + '0';
	c += write(1, &deg, 1);
	return (c);
}
