/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <sisidra@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 02:28:23 by sisidra           #+#    #+#             */
/*   Updated: 2020/07/14 02:28:23 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	set_default(t_frctl *data, char *type)
{
	data->width = 500;
	data->height = 500;
	if (ft_strcmp(type, "julia") == 0)
		julia_set(data);
	else if (ft_strcmp(type, "newthon") == 0)
		newthon_set(data);
	else if (ft_strcmp(type, "mandelbrot") == 0)
		mandelset(data);
	else
		ft_close(data, -1);
	data->m_x = 0;
	data->m_y = 0;
	data->img.bpp = 32;
	data->img.size = data->width * 4;
	data->img.endian = 0;
	data->is_default = 2;
	data->color.col_switch = 0;
	data->color.rgb = 0x7802c1;
	data->color.srgb = 0xf7f43e;
	data->color.step = 0x05;
	set_pallette(&data->color, data->iter);
}

void	julia_set(t_frctl *data)
{
	data->type = 2;
	data->mx = 0.0;
	data->my = -0.8;
	data->zoom = 10.0;
	data->iter = 40;
}

void	mandelset(t_frctl *data)
{
	data->zoom = 150;
	data->iter = 40;
	data->type = 1;
	data->delta_x = data->width * 0.75;
	data->delta_y = data->height / 2;
}

void	newthon_set(t_frctl *data)
{
	data->type = 3;
	data->iter = 40;
	data->zoom = 0.01;
	data->delta_x = data->width / 2;
	data->delta_y = data->height / 2;
	data->rays = -4;
}

void	ft_close(t_frctl *data, int status)
{
	if (status != 0)
		ft_putstr("Please, put a fractol name as argument: \
mandelbrot, julia or newthon!\n");
	else
	{
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free(data);
	}
	exit(0);
}
