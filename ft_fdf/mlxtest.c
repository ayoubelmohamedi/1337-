
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
	char *dst;
	// offset => int offset = (y * line_length + x * (bits_per_pixel / 8));
	dst = data->addr + (y * data->line_length + x * (data ->bits_per_pixel / 6));
	*(unsigned int*)dst = color;
}

size_t ft_getrows(int fd)
{
	size_t rows;
	char *line;
	char *tmp;

	rows = 0;
	line = get_next_line(fd);
	while(line)
	{
		rows++;
		tmp = line;
		line = get_next_line(fd);
		free(tmp);
	}
	return (rows);
}

size_t ft_getcols(int fd)
{
	size_t cols;
	char *line;
	char **split;

	line = get_next_line(fd);
	split = ft_split(line, ' ');
	free(line);
	cols = 0;
	while (split[cols])
		free(&split[cols++]);
	return (cols);
}

int *ft_split_int(const char *line, size_t col)
{
	int *res;
	char **split;
	size_t i;

	i = 0;
	split = ft_split((const char *) line, ' ');
	res = malloc(sizeof(int) * col);
	free((void*)line);
	while (i < col)
	{
		res[i] = ft_atoi((const char*)split[i]);
		free(&split[i]);
		i++;
	}
	free(split);
	return (res);
}

int **ft_genMap(char *filename, size_t rows, size_t cols)
{
	int **map;
	char *line;
	int fd;
	char *tmp;
	size_t i;

	fd = open(filename,O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	map = malloc(sizeof(int*) * rows);
	i = 0;
	while (line)
	{
		tmp = line;
		map[i] = ft_split_int(line, cols);
		line = get_next_line(fd);
		free(tmp);
	}
	return (map);

}

int	main(int ac, char **av)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_data	img2;
	int **map;
	int fd;

	if (ac != 2)
		return (1);
	fd = open(av[1], O_RDONLY);
	size_t cols = ft_getcols(fd);
	printf("cols %zu\n", cols);	
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