
// #include <stdlib.h>
// #include "mlx.h"

#include "ft_fdf.h"

typedef	struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int 	zoom;
	int		offset;
	t_point	**map;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;	

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;	
}

int get_min(int **table)
{
	int min;


	return (min);
}

void	mappirize(t_data *data, int rows, int cols, int color)
{
	char *dst;
	size_t i, j;
	int	new_x, new_y;

	i =0;
	j =0;
	
	while (i < rows)
	{
		while (j++ < cols)
		{
			new_x = ((data->map[i][j].x - data->map[i][j].y) * cos(0.523599)); 
			new_y =  (data->map[i][j].x + (data->map[i][j].y)) * sin(0.523599) - data->map[i][j].z;
			data->map[i][j].x = new_x + 300;
			data->map[i][j].y = new_y + 400;
		
			printf("(%d,%d) ",new_x, new_y);


			// printf("(%d, %d) ", data->map[i][j].x, data->map[i][j].y);	
			if (data->map[i][j].x > 0 && data->map[i][j].y > 0)
				my_mlx_pixel_put(data,data->map[i][j].x , data->map[i][j].y, color);
			else
				printf("\nNegative (%d,%d)\n",new_x, new_y);
			// data->map[i][j].x += 200;
			// data->map[i][j].y += 200;

		}
		j = 0;
		i++;
		printf("\n");
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

	color =	ft_strchr((const char*)text, ',');
	if (!color)
		return (0xFFFFFF);
	color++;
	if (ft_strncmp(color,"0x",2))	
		color += 2;
	return (ft_atoi_base(color,"0123456789abcdef"));
}

t_point	*ft_parseLine(char **splitted, size_t curr_row, size_t cols)
{
	t_point *row_map;
	size_t i;

	i = 0;
	row_map = (t_point*)malloc(sizeof(t_point) * cols);
	while (splitted[i])
	{
		row_map[i].x = curr_row;
		row_map[i].y = i;
		row_map[i].z = ft_atoi(splitted[i]);
		row_map[i].color = ft_fetchColor(splitted[i]);
		i++;
	}
	freeItems((void*)splitted, cols);
	return (row_map);
}

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

	map = ft_genMap(av[1], rows, cols);	
	// print_row(map, rows, cols);

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx,720, 720, "fdf");
	
	img.img = mlx_new_image(mlx, 720, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian); 	
	img.map = map;
	mappirize(&img, rows, cols, 0x00FF0000);
	printTable(map, rows, cols);

	mlx_put_image_to_window(mlx, mlx_win, img.img,0,0);
	mlx_loop(mlx);

}