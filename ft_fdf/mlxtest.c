
#include <stdlib.h>
#include "mlx.h"

#include "ft_fdf.h"

typedef	struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	mappirize(t_data *data, t_point *points, int color)
{
	char *dst;
	// offset => int offset = (y * line_length + x * (bits_per_pixel / 8));
	size_t i, j;
	int right, down;
	int	new_x, new_y;

	right = 0;
	down = 0;
	i =0;
	j =0;
	while (i < rows - 1)
	{
		while (j < cols -1 )
		{
			new_x = points[i]->x + (sqrt(2) / 2) * points[i]->y + (sqrt(2) / 2) * points[i]->z ;
			new_y = points[i]->x - (sqrt(2) / 2) * points[i]->y + (sqrt(2) / 2) * points[i]->z ;

			my_mlx_pixel_put(data, new_x, new_y, 0xFFFFFF);
			right += 4;
			j++;
		}
		right = 0;
		down += 4;
		printf("\n");
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

int 	ft_covertHex(color)
{
	int hex;

	color++;
	if (ft_strncmp(color,"0x",2))	
		color += 2;
	//TODO make atoi_base
	return (ft_atoi_base(color,"0123456789abcdef"));
}

int		ft_fetchColor(char *text)
{
	char *color;

	color =	ft_strchr((const char*)text, ',');
	if (!color)
		return (0xFFFFFF);
	return (ft_covertHex(color));
}

t_map	*ft_parseLine(char **splitted, size_t curr_row, size_t cols)
{
	t_map *row_map;
	size_t i;

	i = 0;
	row_map = (t_map*)malloc(sizeof(t_map*) * (cols + 1));
	while (splitted[i])
	{
		row_map[i]->x = i;
		row_map[i]->y = curr_row;
		row_map[i]->z = ft_atoi(splitted[i]);
		row_map[i]->color = ft_fetchColor(splitted[i]) 
		i++;
	}
	freeItems((void*)splitted, cols);
	row_map[cols + 1] = NULL;
	return (row_map);
}

t_point **ft_genMap(char *filename, size_t rows, size_t cols)
{
	t_point **map;
	t_map	*row_map;
	char *line;
	int fd;
	size_t i;

	fd = open(filename, O_RDONLY);	
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(t_point*) * (rows + 1));
	map[rows+1]= NULL;
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		map[i++] = ft_parseLine(ft_split(line, ' '), cols); 
		free(line);
		line = get_next_line(fd);
		// free(tmp);
	}
	return (map);
}

int	main(int ac, char **av)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_point **map;

	if (ac != 2)
		return (1);
	size_t cols = ft_getcols(av[1]);
	size_t rows = ft_getrows(av[1]);

	//map = ft_genMap(av[1], rows, cols);
	int fd = open(av[1], O_RDONLY);
	char *line = get_next_line(fd);
	// printf("%s \n", line);
	map = ft_genMap(av[1], rows, cols);
	close(fd);
	printf("cols %zu\n", cols);	
	printf("rows %zu\n", rows);	
	mlx = mlx_init();

	mlx_win = mlx_new_window(mlx, 720, 720, "Hello world!");
	img.img = mlx_new_image(mlx, 720, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	mappirize(&img, rows, cols, 0xFFFFFF);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}