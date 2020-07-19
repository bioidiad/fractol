/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <sisidra@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 01:33:49 by sisidra           #+#    #+#             */
/*   Updated: 2020/07/14 01:33:49 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int			mouse_hook(int mousecode, int x, int y, t_frctl *data)
{
	if (mousecode == 4)
	{
		data->m_x = (x - data->delta_x) +
			data->m_x * 1.1 + (0.25 * data->width);
		data->m_y = (y - data->delta_y) + data->m_y * 1.1;
		data->zoom *= 1.1;
		data->iter += 0.1;
	}
	else if (mousecode == 5)
	{
		data->m_x = (data->delta_x - y) + data->m_x * 0.9;
		data->m_y = (data->delta_y - y) + data->m_y * 0.9;
		data->zoom *= 0.9;
		data->iter -= 0.1;
	}
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	treads(data);
	return (0);
}

int			mouse_moove(int x, int y, t_frctl *data)
{
	if (y <= data->height)
	{
		data->mx = (double)x / (data->width);
		data->my = (double)y / (data->height);
	}
	treads(data);
	return (0);
}

int			add_color(int color, int r, int g, int b)
{
	r += (color >> 16) & 0xFF;
	g += (color >> 8) & 0xFF;
	b += (color >> 0) & 0xFF;
	color = r << 16 | g << 8 | b << 0;
	return (color);
}

void		color_manager(t_frctl *data, t_color *color, int key)
{
	int *switcher;

	switcher = NULL;
	if (key == 32)
		data->color.col_switch = data->color.col_switch == 0 ? 1 : 0;
	if (color->col_switch == 0)
		switcher = &color->rgb;
	else
		switcher = &color->srgb;
	if (key == 44)
		*switcher = add_color(*switcher, color->step, 0x00, 0x00);
	else if (key == 46)
		*switcher = add_color(*switcher, 0x00, color->step, 0x00);
	else if (key == 47)
		*switcher = add_color(*switcher, 0x00, 0x00, color->step);
	set_pallette(&data->color, data->iter);
}

int			key_def(int key, t_frctl *data)
{
	if (key == 65307)
		ft_close(data, 0);
	else if (key == 105)
		data->zoom *= 1.2;
	else if (key == 111 && data->zoom < (__DBL_MAX__ - __INT16_MAX__))
		data->zoom *= 0.9;
	else if (key == 65363)
		data->delta_x += 100;
	else if (key == 65361)
		data->delta_x -= 100;
	else if (key == 65362)
		data->delta_y -= 100;
	else if (key == 65364)
		data->delta_y += 100;
	else if (key == 61 && data->iter < 200)
		data->iter += 5;
	else if (key == 114 && data->rays > -8)
		data->rays -= 2;
	else if (key == 44 || key == 46 || key == 47 || key == 32)
		color_manager(data, &data->color, key);
	else
		return (0);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	treads(data);
	return (0);
}
