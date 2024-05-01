
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

void	mappirize(t_data *data, int rows, int cols, int color)
{
	char *dst;
	// offset => int offset = (y * line_length + x * (bits_per_pixel / 8));
	size_t i, j;

	i =0;
	j =0;

	while (i < rows - 1)
	{
		while (j < cols -1 )
		{
			
			mlx_pixel_put(mlx, win, 640/2, 360/2, 0xFFFFFF);
		}
		printf("\n");
		j = 0;
		i++;
	}


}

size_t ft_getrows(char *filename)
{
	size_t rows;
	char *line;
	char *tmp;
	int fd;

	rows = 1;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while(line)
	{
		rows++;
		tmp = line;
		line = get_next_line(fd);
		free(tmp);
	}
	close(fd);
	return (rows);
}

size_t ft_getcols(char *filename)
{
	size_t cols;
	char *line;
	char **split;
	int fd;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	split = ft_split(line, ' ');
	free(line);
	cols = 0;
	while (split[cols])
	{
		cols++;
		free(split[cols-1]);
	}
	free(split);
	close(fd);
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
	while (split[i])
	{
		res[i] = ft_atoi((const char*)split[i]);
		// free(&split[i]);
		i++;
	}
	free((void*)line);
	// free(split);
	return (res);
}

int **ft_genMap(char *filename, size_t rows, size_t cols)
{
	int **map;
	char *line;
	int fd;
	char *tmp;
	size_t i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	map = malloc(sizeof(int*) * rows);
	i = 0;
	while (line)
	{
		tmp = line;
		map[i++] = ft_split_int(line, cols);
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
	t_data	img2;
	int **map;

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
	
	my_mlx_pixel_put(&img, rows,cols,0xffffff);
	mlx_loop(mlx);

}