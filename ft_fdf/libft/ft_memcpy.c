/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:50:51 by ael-moha          #+#    #+#             */
/*   Updated: 2023/11/21 21:19:35 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*sc;
	unsigned char		*dst;

	i = 0;
	sc = (const unsigned char *)src;
	dst = (unsigned char *)dest;
	if (n == 0 || dst == sc)
		return (dst);
	while (i < n)
	{
		dst[i] = sc[i];
		i++;
	}
	return (dst);
}
