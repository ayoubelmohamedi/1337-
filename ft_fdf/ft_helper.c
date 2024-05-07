/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:51:30 by ael-moha          #+#    #+#             */
/*   Updated: 2024/05/07 16:55:36 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_fdf.h"

size_t ft_getrows(char *filename)
{
	size_t rows;
	char *line;
	char *tmp;
	int fd;

	rows = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while(line)
	{
		rows++;
		tmp = line;
		line = get_next_line(fd);
		free(tmp);
	}
	close(fd);
	return (rows);
}

size_t ft_getcols(char *filename)
{
	size_t cols;
	char *line;
	char **split;
	int fd;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	split = ft_split(line, ' ');
	free(line);
	cols = 0;
	while (split[cols])
	{
		cols++;
		free(split[cols-1]);
	}
	free(split);
	close(fd);
	return (cols);
}

int *ft_split_int(const char *line, size_t col)
{
	int *res;
	char **split;
	size_t i;

	i = 0;
	split = ft_split((const char *) line, ' ');
	res = malloc(sizeof(int) * col);
	while (split[i])
	{
		res[i] = ft_atoi((const char*)split[i]);
		// free(&split[i]);
		i++;
	}
	free((void*)line);
	// free(split);
	return (res);
}

