/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:36:30 by ael-moha          #+#    #+#             */
/*   Updated: 2024/08/21 16:01:10 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	init_camera(t_data *data)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	camera->x_angle = -asin(1 / sqrt(3));
	camera->y_angle = 1 / sqrt(3);
	camera->z_angle = asin(1 / sqrt(3));
	camera->zoom = ft_min((double)data->width / data->cols, (double)data->height
			/ data->rows);
	data->camera = camera;
}

void	ft_rotation_x(t_point *dest_p, t_data *data)
{
	t_point	*tmp;

	tmp = dest_p;
	dest_p->y = tmp->y * cos(data->camera->x_angle) + tmp->z
		* sin(data->camera->x_angle);
	dest_p->z = -tmp->y * sin(data->camera->x_angle) + tmp->z
		* cos(data->camera->x_angle);
}

void	ft_rotation_y(t_point *dest_p, t_data *data)
{
	t_point	*tmp;

	tmp = dest_p;
	dest_p->x = tmp->x * cos(data->camera->y_angle) - tmp->z
		* sin(data->camera->y_angle);
	dest_p->z = -tmp->x * sin(data->camera->y_angle) + tmp->z
		* cos(data->camera->y_angle);
}

void	ft_rotation_z(t_point *dest_p, t_data *data)
{
	t_point	*tmp;

	tmp = dest_p;
	dest_p->x = tmp->x * cos(data->camera->z_angle) - tmp->y
		* sin(data->camera->z_angle);
	dest_p->y = tmp->x * sin(data->camera->z_angle) + tmp->y
		* cos(data->camera->z_angle);
}

t_point	ft_project(t_point p, t_data *data)
{
	t_point	dest_p;

	dest_p = p;
	ft_rotation_x(&dest_p, data);
	ft_rotation_y(&dest_p, data);
	ft_rotation_z(&dest_p, data);
	dest_p.x *= data->camera->zoom;
	dest_p.y *= data->camera->zoom;
	dest_p.x += (data->width) / 2;
	dest_p.y += data->height / 2 - (data->camera->zoom * (data->rows / 2));
	dest_p.color = p.color;
	return (dest_p);
}
