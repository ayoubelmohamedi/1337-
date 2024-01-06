/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:49:02 by ael-moha          #+#    #+#             */
/*   Updated: 2023/12/22 13:49:17 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf.h"

int	ft_handle(char spec, va_list *args)
{
	int	c;

	c = 0;
	if (spec == 'd' || spec == 'i')
		c = ft_handle_nbr(va_arg(*args, int));
	else if (spec == 'u')
		c = ft_handle_usign(va_arg(*args, unsigned int));
	else if (spec == 'x' || spec == 'X')
		c = ft_handle_hex(va_arg(*args, int), spec);
	else if (spec == 'c')
		c = ft_handle_char(va_arg(*args, int));
	else if (spec == 's')
		c = ft_hande_str(va_arg(*args, char *));
	else if (spec == 'p')
		c = ft_handleptr(va_arg(*args, void *));
	return (c);
}
#include <stdio.h>
#include <string.h>

int ft_strchr(char c)
{
	char *str;

	str = "diuxXcsp";
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}
int	ft_printf(char *content, ...)
{
	int		c;
	va_list	args;
	char	*ptr;

	if (!content)
		return (-1);
	va_start(args, content);
	ptr = content;
	c = 0;
	while (*ptr)
	{
		if (*ptr == '%')
		{
			ptr++;
			if (*ptr == '%')
				c += write(1, ptr++, 1);
			else if (*ptr == '\0')
				break;
			else if ()
				c += ft_handle(*ptr++, &args);
		}
		else
			c += write(1, ptr++, 1);
	}
	va_end(args);
	return (c);
}
int main()
{
	int tot = ft_printf("%");
	ft_printf("%d",tot);
	return (0);
}
