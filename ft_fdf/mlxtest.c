
// #include <stdlib.h>
// #include "mlx.h"

#include "ft_fdf.h"

int key_press(int keycode, t_data *data) {
    printf("Key code: %d\n", keycode);
	if (keycode == 65307)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx,data->win);
		// exit(0);
	}
	//up-down arrow
	if (keycode == 65362)
	{	
		data->zoom += 1;
		if (data->img)
			mlx_destroy_image(data->mlx,data->img);	
		data->img = mlx_new_image(data->mlx, data->width, data->height);
		mappirize(data, data->rows, data->cols, 0xFFFFFF);		
		// mlx_put_image_to_window(data->mlx, data->win, data->img, data->width, data->height);	
		// mlx_loop(data->mlx);	
	}
	else if (keycode == 65364 && data->zoom > 1)
	{
		data->zoom -= 1;
		// mlx_destroy_image(data->win,data->img);	
		// mlx_new_image(data->img, data->width, data->height);
		// mlx_loop(data->mlx);
	}
    return (0);
}


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;	

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;	
}

double arcsin(double x) {
    if (x < -1 || x > 1) {
        // Input value is out of range
        return NAN;
    }
    return atan(x / sqrt(1 - x * x));
}

void	mappirize(t_data *data, size_t rows, size_t cols, int color)
{
	char *dst;
	size_t i, j;
	int	new_x, new_y;
	float		teta = data->angle;
	printf("teta from data->angle => %f\n", teta);
	// float teta  =  0.523599; 
	// float teta  =  0.7071067811865475; 

	i =0;
	j =0;
	
	while (i < rows)
	{
		while (j++ < cols)
		{
			new_x = ((data->map[i][j].x - data->map[i][j].y) * cos(teta)); 
			new_y =  (data->map[i][j].x + (data->map[i][j].y)) * sin(teta) - data->map[i][j].z;
			data->map[i][j].x = (new_x * data->zoom + data->width / 2);
			data->map[i][j].y = (new_y * data->zoom +  data->height / 2);
		
			printf("(%d,%d) ",new_x, new_y);
			// printf("(%d, %d) ", data->map[i][j].x, data->map[i][j].y);	
			if (data->map[i][j].x > 0 && data->map[i][j].x < data->width && data->map[i][j].y > 0 && data->map[i][j].y < data->height)
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

	img.mlx = mlx;	
	img.win = mlx_win;
	img.img = mlx_new_image(mlx, 720, 720);
	img.width = 720;
	img.height = 720;
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian); 	
	img.map = map;
	img.angle = 0.523599; 
	img.zoom = 4;
	mappirize(&img, rows, cols, 0xFFFFFF);
	printTable(map, rows, cols);

	mlx_put_image_to_window(mlx, mlx_win, img.img,0,0);
	mlx_key_hook(mlx_win,  &key_press, &img);
	mlx_loop(mlx);

}