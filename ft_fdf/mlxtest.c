
#include "ft_fdf.h"

t_data *get_data(t_data *new)
{
	static t_data data;

	if (new != NULL )
		data  = *new;

	return (&data);
}

int scroll_hook(int keycode, t_data *nothing) {
    
    // Zoom in on scroll up, zoom out on scroll down
	printf("mouse wheel is %d\n" , keycode);
	t_data *data = get_data(NULL);
	printf("inside %p\n", data);	

	printf("INFO\n hight  = %d \n width = %d , zoom = %f\n", data->height, data->width, data->zoom);

    if (keycode == 5) {
        // Zoom in

		printf("scroll up\n");
        data->zoom += 0.8;
    } else if (keycode == 4) {
		printf("scroll down\n");
		data->zoom -= 0.8;
        // Zoom out
        // data->zoom -= 0.8;
    }
	ft_display(data);

	return (0);
}

int key_press(int keycode, t_data *noth) {

	t_data * data = get_data(NULL);
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
		data->angle_y += 0.1;
	if (keycode == ARROW_DOWN  && data->zoom > 1)
		data->angle_y -= 0.1;
	if (keycode == ARROW_RIGHT)
		data->angle_x += 0.1;
	if (keycode == ARROW_LEFT)
		data->angle_x -= 0.1;
	ft_display(data);
    return (0);
}

void ft_display(t_data *data)
{
	if (data->map)
	{
		mlx_destroy_image(data->mlx,data->img);//
		data->img = mlx_new_image(data->mlx,data->width, data->height);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);

		printf("rotation of teta (x) = %f\n", data->angle_x);
		printf("rotation of beta (y) = %f\n", data->angle_y);


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

void ft_rotationX(t_point * dest_p, t_data * data)
{
	t_point *tmp = dest_p;

	dest_p->x = tmp->x;
	dest_p->y = tmp->y * cos(data->angle_x) + tmp->z * sin(data->angle_x);
	dest_p->z = -tmp->y * sin(data->angle_x) + tmp->z * cos(data->angle_x);
}

void ft_rotationY(t_point * dest_p, t_data * data)
{
	t_point *tmp = dest_p; 

	dest_p->x = tmp->x * cos(data->angle_y) - tmp->z * sin(data->angle_y);
	dest_p->y = tmp->y;
	dest_p->z = tmp->x * sin(data->angle_y) + tmp->z * cos(data->angle_y);
}

t_point		ft_project (t_point p, t_data * data)
{
	t_point dest_p;

	// p.z = p.z * (sin(data.angle_y) + );
	dest_p = p;
	ft_rotationX(&dest_p, data);
	ft_rotationY(&dest_p, data);
	// p.z *= sin(data->angle_y) + cos(data->angle_y);
	// new_x = p.x + (cos(data->angle_y) - sin(data->angle_y));
	// new_y = p.y + (cos(data->angle_x) + p.z * sin(data->angle_x));

	// new_x *= -1;
	// new_y *= -1;
	// new_x = data->angle * (p.x * sqrt(3) - p.z * sqrt(3));
	// new_y = (data->angle * (p.x + 2 * p.y + p.z));
	// new_x = p.x * data->angle;
	// new_y = p.y * data->angle;

	dest_p.x *= data->zoom;
	dest_p.y *= data->zoom;
	dest_p.x += (data->width) / 2;
	dest_p.y += data->height / 2 - (data->zoom * (data->rows / 2));

	// printf("original image is %d\n", )

	dest_p.color = p.color;	
	return (dest_p);
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
	// img->angle = 0.523599;
	img->angle_x = asin(1/sqrt(3));
	img->angle_y = 45;

	// img->angle_x = 0;
	// img->angle_y = 0;

	img->zoom = (double)(750 /2) / max(img->cols, img->rows);
	img->zoom = (double) (750 / 2) / 750;

	img->offset = 720 / 2;

	mappirize(img);
	mlx_put_image_to_window(img->mlx, mlx_win, img->img,0,0);

	get_data(img);
	mlx_key_hook(img->win, key_press, NULL);
	
	mlx_mouse_hook(img->win, scroll_hook, NULL);
	mlx_loop(mlx);	
}