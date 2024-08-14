

#include "ft_fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;	

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;	
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

double ft_min(double a, double b)
{
	if (a > b)
		return (a);
	return (b);	
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
	double dx;
	double dy;
	double pixelY;
	double pixelX;
	int pixels;

	dx = p2.x - p1.x; 
	dy =  p2.y - p1.y; 
	pixels = sqrt((dx * dx) + (dy * dy));
	dx /= pixels;
	dy /= pixels;

	pixelY = p1.y;
	pixelX = p1.x;
	while (pixels--)
	{
		if (pixelX > 0 && pixelX < data->width 
			&& pixelY > 0 && pixelY < data->height)
			my_mlx_pixel_put(data , pixelX, pixelY , p1.color);
		pixelX += dx;
		pixelY += dy;
	}
}

