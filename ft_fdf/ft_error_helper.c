/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:08:13 by ael-moha          #+#    #+#             */
/*   Updated: 2024/08/21 23:08:34 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

size_t	ft_count_elements(char **str)
{
	size_t	c;

	c = 0;
	while (str[c] != NULL)
		c++;
	return (c);
}

void	free_split(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

size_t	count_cols(char *line)
{
	size_t	c;
	char	**split;

	while (*line == ' ')
		line++;
	split = ft_split(line, ' ');
	c = ft_count_elements(split);
	free_split(split);
	return (c);
}

size_t	ft_getcols_line(char *line)
{
	size_t	cols;
	char	**split;

	split = ft_split(line, ' ');
	free(line);
	cols = 0;
	while (split[cols])
	{
		cols++;
		free(split[cols - 1]);
	}
	free(split);
	return (cols);
}
