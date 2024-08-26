/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:08:09 by ael-moha          #+#    #+#             */
/*   Updated: 2024/08/21 23:08:24 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	ft_error(char *filename, int error)
{
	size_t	l;
	char	*msg;
	char	*msg2;

	msg = "Found wrong line length. Exiting.\n";
	msg2 = "No file ";
	l = ft_strlen(filename);
	if (error == 0)
		write(1, msg, 34);
	else if (error == 1)
	{
		write(1, msg2, 8);
		write(1, filename, l);
		write(1, "\n", 1);
		exit(1);
	}
	else
	{
		write(1, "No data found.\n", 15);
		exit(1);
	}
}

static int	is_extension_valid(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	filename += len - 4;
	if (ft_strncmp(filename, ".fdf", 4) == 0)
		return (1);
	return (0);
}

static int	is_file_valid(char *filename)
{
	size_t	cols;
	size_t	c;
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	c = ft_getcols(filename);
	line = get_next_line(fd);
	while (line)
	{
		cols = ft_getcols_line(line);
		if (cols == 0)
			return (0);
		line = get_next_line(fd);
	}
	get_next_line(-5);
	return (1);
}

static void	is_file_empty(char *filename)
{
	int		fd;
	char	*line;
	size_t	i;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	close(fd);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line == NULL || *line == '\n')
	{
		free(line);
		ft_error(filename, 2);
	}
	else
		free(line);
}

int	is_valid(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error(filename, 1);
	close(fd);
	if (filename && is_extension_valid(filename))
	{
		is_file_empty(filename);
		if (!is_file_valid(filename))
		{
			ft_error(filename, 0);
			return (0);
		}
		return (1);
	}
	ft_error(filename, 0);
	return (0);
}
