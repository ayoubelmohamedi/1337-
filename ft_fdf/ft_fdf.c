/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:09:10 by ael-moha          #+#    #+#             */
/*   Updated: 2024/08/21 23:46:46 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

t_data	*get_data(t_data *new)
{
	static t_data	data;

	if (new != NULL)
		data = *new;
	return (&data);
}

int	scroll_hook(int keycode, t_data *data)
{
	data = get_data(NULL);
	if (keycode == MOUSE_WHEEL_DOWN)
	{
		data->camera->zoom += 0.8;
	}
	else if (keycode == MOUSE_WHEEL_UP)
	{
		if (data->camera->zoom - 0.8 > 1)
			data->camera->zoom -= 0.8;
	}
	ft_display(data);
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	data = get_data(NULL);
	if (keycode == ESCAPE)
		ft_destroy(data);
	if (keycode == ARROW_UP)
		data->camera->y_angle += 0.1;
	if (keycode == ARROW_DOWN && data->camera->zoom > 1)
		data->camera->y_angle -= 0.1;
	if (keycode == ARROW_RIGHT)
		data->camera->x_angle += 0.1;
	if (keycode == ARROW_LEFT)
		data->camera->x_angle -= 0.1;
	ft_display(data);
	return (0);
}

void	init_data(t_data *data, char *filename)
{
	data->mlx = mlx_init();
	data->rows = ft_getrows(filename);
	data->cols = ft_getcols(filename);
	data->width = WIDTH;
	data->height = HEIGHT;
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->win = mlx_new_window(data->mlx, data->height, data->width, "fdf");
	data->map = ft_gen_map(filename, data->rows, data->cols);
	data->offset = 720 / 2;
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2 || (!is_valid(av[1])))
		return (1);
	data = get_data(NULL);
	init_data(data, av[1]);
	init_camera(data);
	mappirize(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_key_hook(data->win, key_press, NULL);
	mlx_hook(data->win, 17, 1L << 2, ft_destroy, data);
	mlx_mouse_hook(data->win, scroll_hook, NULL);
	mlx_loop(data->mlx);
	return (0);
}
