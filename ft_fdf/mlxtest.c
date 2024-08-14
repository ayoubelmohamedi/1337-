
#include "ft_fdf.h"


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
	mlx_win = mlx_new_window(mlx,HIGHT, WIDTH, "fdf");

	img->mlx = mlx;	
	img->win = mlx_win;
	img->width = WIDTH;
	img->height = HIGHT;
	img->img = mlx_new_image(mlx, img->width, img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian); 	
	img->map = map;
	// img->angle = 0.523599;
	// img->angle_x = asin(1/sqrt(3));
	// img->angle_y = 45;

	t_camera camera = {-asin(1/sqrt(3)) , 1/sqrt(3), asin(1/sqrt(3)), 0.5};
	// angles.x_angle = asin(1/sqrt(3));
	// angles.y_angle = 45;
	// angles.z_angle = 0;
	// angles.zoom = (double) (750 / 2) / 750; 
	camera.zoom = ft_min((double)img->width / img->cols,
			(double)img->height / img->rows);

	printf("cols is => %zu\n", img->cols);
	// if (camera.zoom < 1)

	printf("img.height / img->cols / 2 => %f\n", (double) img->height / img->cols / 2);
	printf("img->height / img->rows / 2 => %f\n", (double) img->height / img->rows / 2);
	printf("zoom val => %f\n", camera.zoom);
	// camera.zoom = 9;
	// camera.zoom = 1.5;

	img->camera = &camera;	

	// img->zoom = (double)(750 /2) / max(img->cols, img->rows);
	// img->zoom = (double) (750 / 2) / 750;

	img->offset = 720 / 2;

	mappirize(img);
	mlx_put_image_to_window(img->mlx, mlx_win, img->img,0,0);

	get_data(img);
	mlx_key_hook(img->win, key_press, NULL);
	
	mlx_mouse_hook(img->win, scroll_hook, NULL);
	mlx_loop(mlx);	
}