/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:12:48 by ael-moha          #+#    #+#             */
/*   Updated: 2024/08/21 23:10:09 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

double	ft_min(double a, double b)
{
	if (a > b)
		return (b);
	return (a);
}

void	free_map(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->rows)
		free(data->map[i++]);
	free(data->map);
	data->map = NULL;
}

void	draw_line(t_data *data, t_point p1, t_point p2)
{
	double	dx;
	double	dy;
	double	pixel_y;
	double	pixel_x;
	int		pixels;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	pixels = sqrt((dx * dx) + (dy * dy));
	dx /= pixels;
	dy /= pixels;
	pixel_y = p1.y;
	pixel_x = p1.x;
	while (pixels--)
	{
		if (pixel_x > 0 && pixel_x < data->width && pixel_y > 0
			&& pixel_y < data->height)
			my_mlx_pixel_put(data, pixel_x, pixel_y, p1.color);
		pixel_x += dx;
		pixel_y += dy;
	}
}
