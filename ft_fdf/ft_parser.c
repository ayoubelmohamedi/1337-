
#include "ft_fdf.h"

t_point **ft_genMap(char *filename, size_t rows, size_t cols)
{
	t_point **map;
	char *line;
	int fd;
	size_t i;

	fd = open(filename, O_RDONLY);	
	if (fd < 0)
		return (NULL);
	map = (t_point**)malloc(sizeof(t_point*) * rows);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		map[i] = ft_parseLine(ft_split(line, ' '), i, cols); 
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (map);
}

void	mappirize(t_data *data)
{
	char *dst;
	size_t i, j;
	t_point p1;

	i =0;
	j =0;
	while (i < data->rows - 1)
	{
		while (j < data->cols - 1)
		{
			draw_line(data, ft_project(data->map[i][j], data) ,ft_project(data->map[i][j + 1], data), data->map[i][j].color);
			draw_line(data, ft_project(data->map[i][j], data) ,ft_project(data->map[i + 1][j], data), data->map[i][j].color);
			j++;
		}
		j = 0;
		i++;
	}
}

void	freeItems(void **item, size_t cols)
{
	size_t i;

	i = 0;
	while (i < cols)
		free(item[i++]);
	free(item);
}

int		ft_fetchColor(char *text)
{
	char *color;
	char *upper_color;

	color =	ft_strchr((const char*)text, ',');
	if (!color)
		return (DEFAULT_COLOR);
	color++;
	if (!ft_strncmp(color,"0x",2))	
		color += 2;
	ft_upper_str(color);
	return (ft_atoi_base(color,BASE16));
}

t_point	*ft_parseLine(char **splitted, int curr_row, size_t cols)
{
	t_point *row_map;
	size_t i;

	i = 0;
	row_map = (t_point*)malloc(sizeof(t_point) * cols);	
	while (splitted[i] && i < cols)
	{
		row_map[i].x = curr_row;
		row_map[i].y = i;
		row_map[i].z = ft_atoi(splitted[i]);
		row_map[i].color = ft_fetchColor(splitted[i]);
		i++;
	}
	freeItems((void**)splitted, cols);
	return (row_map);
}
