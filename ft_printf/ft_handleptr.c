/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handleptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:47:30 by ael-moha          #+#    #+#             */
/*   Updated: 2023/12/22 13:47:44 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_handleptr(void *ptr)
{
	int	c;

	if (!ptr)
		return (write(1, "(nil)", 5));
	c = 2;
	write(1, "0x", 2);
	c += ft_handle_hex(ft_handle_usign(ptr), 'x');
	return (c);
}
