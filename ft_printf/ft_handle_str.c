/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:48:37 by ael-moha          #+#    #+#             */
/*   Updated: 2023/12/22 13:48:55 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_handle_char(int c)
{
	return (write(1, &c, 1));
}

int	ft_hande_str(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (write(1,"(null)",6));
	while (str[i])
		write(1, &str[i++], 1);
	return (i);
}