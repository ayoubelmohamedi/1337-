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
#include "printf.h"

int	ft_handle_usign(unsigned int nbr)
{
	char	deg;

	if (nbr / 10 > 0)
		ft_handle_usign(nbr / 10);
	deg = (nbr % 10) + '0';
	write(1, &deg, 1);
	return (ft_count(nbr));
}
