/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:18:49 by ael-moha          #+#    #+#             */
/*   Updated: 2023/12/06 22:24:33 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strcount(const char *s, char c)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (s != NULL && *s != '\0')
	{
		if (*s != c && i == 0)
		{
			i = 1;
			count++;
		}
		else if (*s == c)
			i = 0;
		s++;
	}
	return (count);
}

static size_t	ft_charcount(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static int	ft_free(char **words, size_t i)
{
	if (words[i] == NULL)
	{
		while (i--)
			free(words[i]);
		free(words);
		return (1);
	}
	return (2);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	numstr;
	char	**words;

	numstr = ft_strcount(s, c);
	words = (char **)malloc((numstr + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	i = 0;
	while (s && *s && i < numstr)
	{
		while (*s == c)
			s++;
		count = ft_charcount(s, c);
		words[i] = (char *)malloc(count + 1);
		if (ft_free(words, i) == 1)
			return (NULL);
		ft_strlcpy(words[i], s, count + 1);
		s = s + count;
		i++;
	}
	words[numstr] = NULL;
	return (words);
}
