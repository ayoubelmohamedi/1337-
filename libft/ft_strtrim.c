/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:25:05 by ael-moha          #+#    #+#             */
/*   Updated: 2023/11/21 22:52:54 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	l;
	size_t	r;

	if (!s1 || !set)
		return (NULL);
	l = 0;
	r = ft_strlen(s1);
	while (s1[l] && ft_strchr(set, (char)s1[l]))
		l++;
	while (r > l && ft_strchr(set, (char)s1[r - 1]))
		r--;
	res = (char *)malloc(r - l + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, &s1[l], r - l + 1);
	return (res);
}
