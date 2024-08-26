/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:36:24 by ael-moha          #+#    #+#             */
/*   Updated: 2024/08/21 23:43:36 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

t_point	**ft_gen_map(char *filename, size_t rows, size_t cols)
{
	t_point	**map;
	char	*line;
	int		fd;
	size_t	i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = (t_point **)malloc(sizeof(t_point *) * rows);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		map[i] = ft_parse_line(ft_split(line, ' '), i, cols);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (map);
}

void	mappirize(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < data->rows - 1)
	{
		while (j < data->cols - 1)
		{
			draw_line(data, ft_project(data->map[i][j], data),
				ft_project(data->map[i][j + 1], data));
			draw_line(data, ft_project(data->map[i][j], data),
				ft_project(data->map[i + 1][j], data));
			j++;
		}
		j = 0;
		i++;
	}
}

int	ft_fetch_color(char *text)
{
	char	*color;

	color = ft_strchr((const char *)text, ',');
	if (!color)
		return (DEFAULT_COLOR);
	color++;
	if (!ft_strncmp(color, "0x", 2))
		color += 2;
	ft_upper_str(color);
	return (ft_atoi_base(color, BASE16));
}

t_point	*ft_parse_line(char **splitted, int curr_row, size_t cols)
{
	t_point	*row_map;
	size_t	i;

	i = 0;
	row_map = (t_point *)malloc(sizeof(t_point) * cols);
	while (splitted[i] && i < cols)
	{
		row_map[i].x = curr_row;
		row_map[i].y = i;
		row_map[i].z = ft_atoi(splitted[i]);
		row_map[i].color = ft_fetch_color(splitted[i]);
		i++;
	}
	free_split(splitted);
	return (row_map);
}

int	ft_destroy(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	if (data->map)
		free_map(data);
	get_next_line(-5);
	free(data->camera);
	exit(0);
	return (0);
}
