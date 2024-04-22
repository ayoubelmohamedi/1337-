/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:17:04 by ael-moha          #+#    #+#             */
/*   Updated: 2023/12/12 19:39:26 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	t;

	if (len == 0 && !haystack)
		return (NULL);
	if (*needle == '\0' || haystack == needle)
		return ((char *)haystack);
	i = 0;
	t = len;
	while (*haystack && i < len && (t >= ft_strlen(needle)))
	{
		if (ft_strncmp(haystack, needle, ft_strlen(needle)) == 0)
			return ((char *)haystack);
		i++;
		t--;
		haystack++;
	}
	return (NULL);
}
