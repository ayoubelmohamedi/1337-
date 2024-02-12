/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:43:04 by ael-moha          #+#    #+#             */
/*   Updated: 2024/02/12 17:03:51 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	l;
	size_t	i;
	char	*word;

	i = 0;
	if (!s1 || !s2)
		return (0);
	l = ft_strlen(s1) + ft_strlen(s2);
	word = (char *)malloc(sizeof(char) * (l + 1));
	if (!word)
		return (0);
	while (s1[i])
	{
		word[i] = s1[i];
		i++;
	}
	l = i;
	i = 0;
	while (s2[i])
		word[l++] = s2[i++];
	word[l] = '\0';
	return (word);
}

char	*ft_strdup(char *s)
{
	char	*ptr;
	size_t	i;

	ptr = malloc(ft_strlen(s) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_substr(char *s, size_t start, size_t len)
{
	char	*dup;
	size_t	size;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen || slen == 0)
		return (ft_strdup(""));
	if (slen < start + len)
		size = slen - start + 1;
	else
		size = len + 1;
	dup = (char *)malloc(sizeof(char) * size);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s + start, size);
	return (dup);
}

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t i;
	size_t srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}