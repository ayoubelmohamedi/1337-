/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:36:56 by ael-moha          #+#    #+#             */
/*   Updated: 2024/08/21 16:05:34 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_errors(char *str, char *base)
{
	int		i;
	size_t	b_len;

	b_len = ft_strlen(base);
	if (!base || (b_len < 2))
		return (1);
	i = 1;
	while (base[i])
	{
		if (ft_strchr(&base[i], base[i - 1]))
			return (1);
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (!ft_strchr(base, str[i++]))
			return (1);
	}
	return (0);
}

static int	get_nbr(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (i);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	res;
	int	sign;
	int	base_length;

	res = 0;
	i = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	if (check_errors(str, base))
		return (0);
	base_length = ft_strlen(base);
	while (str[i])
		res = (res * base_length) + (get_nbr(str[i++], base));
	return (res * sign);
}
