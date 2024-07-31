/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:36:56 by ael-moha          #+#    #+#             */
/*   Updated: 2024/05/07 16:37:20 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"


static  int get_base_length(char *base)
{
	int	base_length;
	int	j;

	base_length = 0;
	while (base[base_length])
	{
		if (base[base_length] == '-' || base[base_length] == '+')
			return (0);
		j = base_length + 1;
		while (base[j])
		{
			if (base[base_length] == base[j])
				return (0);
			++j;
		}
		++base_length;
	}
	if (base_length < 2)
		return (0);
	return (base_length);
}

static  int	check_errors(char *str, char *base)
{
	int	i;
	size_t b_len;

	b_len = ft_strlen(base);
	if (!base || b_len < 2)
		return (1);	
	i = 1;
	while(base[i])
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

static  int	get_nbr(char c, char *base)
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

	sign = 1;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	if (*str == )
	if (!(base_length = get_base_length(base)) || check_errors(str, base))
		return (0);
	res = 0;
	sign = 1;
	
	while (str[i])
		res = (res * base_length) + (get_nbr(str[i++], base));
	return (res * sign);
}