
#include "ft_fdf.h"

int key_press(int keycode, t_data *data) {
	printf("key pressed is %d\n" , keycode);
	if (keycode == ESCAPE)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx,data->win);
		if (data->map)
			freeMap(data);
		if (data)
			free(data);
		exit(0);
	}
	//up-down arrow
	if (keycode == ARROW_UP)
		data->zoom += 0.8;
	if (keycode == ARROW_DOWN  && data->zoom > 1)
		data->zoom -= 0.8;
	ft_display(data);
    return (0);
}

void ft_display(t_data *data)
{
	if (data->map)
	{
		mlx_destroy_image(data->mlx,data->img);
		data->img = mlx_new_image(data->mlx,data->width, data->height);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
		mappirize(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img,0,0);
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;	

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;	
}

t_point		ft_project (t_point p, t_data * data)
{
	double new_x;
	double new_y;
	t_point new_p;

	// p = malloc(sizeof(t_point));
	new_x = ((p.x - p.y) * cos(data->angle)); 
	new_y =  (p.x + p.y) * sin(data->angle) - p.z;

	new_x *= data->zoom;
	new_y *= data->zoom;
	new_x += (data->width) / 2;
	new_y += data->height / 2 - (data->zoom * (data->rows / 2));

	// new_p = {new_x , new_y, 0, 0xFFFFFF};

	new_p.x = new_x;
	new_p.y = new_y;
	// if (new_x < 0)
	// 	new_p.x = 0;
	// if (new_y < 0)
	// 	new_p.y = 0;
	new_p.z = 0;
	new_p.color = p.color;	
	return (new_p);
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

void ft_upper_str(char * text)
{
	size_t i;

	i = 0;
	while (text[i])
	{
		if (text[i] >= 'a' && text[i] <= 'z')
			text[i] = text[i] - 32;
		i++;
	}
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

int max(int a, int b) {
    return (a > b) ? a : b;
}

void freeMap(t_data * data)
{
	size_t i;

	i = 0;
	while (i < data->rows)
		free(data->map[i++]);
	free(data->map);
}

void draw_line(t_data * data,t_point p1, t_point p2, int color)
{
	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;

	int pixels = sqrt((dx * dx) + (dy * dy));
	dx /= pixels;
	dy /= pixels;

	double pixelY = p1.y;
	double pixelX = p1.x;
	
	while (pixels--)
	{
		if (pixelX > 0 && pixelX < data->width 
			&& pixelY > 0 && pixelY < data->height)
			my_mlx_pixel_put(data , pixelX, pixelY , p1.color);
		pixelX += dx;
		pixelY += dy;
	}
}

int	main(int ac, char **av)
{
	void	*mlx;
	void	*mlx_win;
	t_data	*img;
	t_point **map;

	if (ac != 2)
		return (1);

	img = malloc(sizeof(t_data));
	img->cols = ft_getcols(av[1]);
	img->rows = ft_getrows(av[1]);

	map = ft_genMap(av[1], img->rows, img->cols);		

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx,720, 720, "fdf");

	img->mlx = mlx;	
	img->win = mlx_win;
	img->width = 720;
	img->height = 720;
	img->img = mlx_new_image(mlx, img->width, img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian); 	
	img->map = map;
	img->angle = 0.523599;
	img->zoom = (double)(750 /2) / max(img->cols, img->rows);
	img->zoom = (double) (750 / 2) / 750;
	
	img->offset = 720 / 2;

	mappirize(img);
	mlx_put_image_to_window(img->mlx, mlx_win, img->img,0,0);
	mlx_key_hook(img->win, key_press, img);
	mlx_loop(mlx);	
}