
#include <stdlib.h>
#include "mlx.h"

#include <ft_fdf.h>

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
	char *dst;
	// offset => int offset = (y * line_length + x * (bits_per_pixel / 8));
	dst = data->addr + (y * data->line_length + x * (data ->bits_per_pixel / 6));
	*(unsigned int*)dst = color;
}

int *ft_split_int(char *line)
{
	int *res;
	char *split;
	size_t i;

	i = 0;
	split = ft_split();
	while (line[i])	
	{

	}


	return (res);
}

char **ft_genMap(char *filename)
{
	char **map;
	char *line;
	int fd;

	fd = open(filename,O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		map[i] = ft_split_int(line);
		line = get_next_line(fd);
	}



	return (map);

}

int	main(itn ac, char **av)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_data	img2;
	int **map;
	int fd;

	if (ac != 2)
		return (1);
	map = ft_genMap(av[1]);
	if (!map)
		return (1);
	mlx = mlx_init();

	mlx_win = mlx_new_window(mlx, 720, 720, "Hello world!");
	img.img = mlx_new_image(mlx, 720, 720);

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
	&img.endian);
	my_mlx_pixel_put(&img,5,5,16711680);
	mlx_put_image_to_window(mlx, mlx_win,  img.img, 0, 0);
	my_mlx_pixel_put(&img,10, 10,0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win,  img.img, 0, 0);
	mlx_loop(mlx);



}