
#include "ft_fdf.h"

void init_camera(t_camera * camera, t_data * data)
{
	camera->x_angle = -asin(1/sqrt(3));
	camera->y_angle = 1/sqrt(3) ;
	camera->z_angle  = asin(1/sqrt(3));
	camera->zoom = ft_min((double)data->width / data->cols,
			(double)data->height / data->rows);
	data->camera = camera;
}

void ft_rotationX(t_point * dest_p, t_data * data)
{
	t_point *tmp;
    
    tmp = dest_p;
	dest_p->y = tmp->y * cos(data->camera->x_angle) + tmp->z * sin(data->camera->x_angle);
	dest_p->z = -tmp->y * sin(data->camera->x_angle) + tmp->z * cos(data->camera->x_angle);
}

void ft_rotationY(t_point * dest_p, t_data * data)
{
	t_point *tmp;
    
    tmp = dest_p; 
	dest_p->x = tmp->x * cos(data->camera->y_angle) - tmp->z * sin(data->camera->y_angle);
	dest_p->z = -tmp->x * sin(data->camera->y_angle) + tmp->z * cos(data->camera->y_angle);
}

void ft_rotationZ(t_point * dest_p, t_data * data)
{
	t_point *tmp = dest_p; 

	dest_p->x = tmp->x * cos(data->camera->z_angle) - tmp->y * sin(data->camera->z_angle);
	dest_p->y = tmp->x * sin(data->camera->z_angle) + tmp->y * cos(data->camera->z_angle);
}

t_point		ft_project (t_point p, t_data * data)
{
	t_point dest_p;

	dest_p = p;
	ft_rotationX(&dest_p, data);
	ft_rotationY(&dest_p, data);
	ft_rotationZ(&dest_p, data);

	dest_p.x *= data->camera->zoom;
	dest_p.y *= data->camera->zoom;
	dest_p.x += (data->width) / 2;
	dest_p.y += data->height / 2 - (data->camera->zoom * (data->rows / 2));
	dest_p.color = p.color;	
	return (dest_p);
}
