/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <sisidra@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 02:30:12 by sisidra           #+#    #+#             */
/*   Updated: 2020/07/14 02:30:12 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	set_pallette(t_color *color, int iter)
{
	float	step;
	float	colr;
	int		i;
	int		j;
	int		b;

	j = 0;
	b = 16;
	step_count(color, (float)iter);
	step = color->step_r;
	while (j < 3)
	{
		i = 0;
		colr = (color->rgb >> b) & 0xFF;
		color->scolr = (color->srgb >> b) & 0xFF;
		while (i <= 254)
			color->pallete[j][i++] = 0;
		i = 0;
		while (i++ < iter)
			color->pallete[j][i] = colr >= color->scolr ? (colr -= step) : \
			(colr += step);
		j++;
		step = j == 1 ? color->step_g : color->step_b;
		b -= 8;
	}
}

void	get_color(t_frctl *data, t_color *color, int i, int pos)
{
	int	r;
	int	g;
	int	b;
	int	rgb;

	if (i >= data->iter)
		rgb = data->type == 1 ? 0x000000 : 0xFFFFFF;
	else
		rgb = color->pallete[0][i] << 16 | color->pallete[1][i] << 8 |\
			color->pallete[2][i];
	r = (rgb >> 16) & 0xFF;
	g = (rgb >> 8) & 0xFF;
	b = (rgb >> 0) & 0xFF;
	data->img.data[pos] = b;
	data->img.data[pos + 1] = g;
	data->img.data[pos + 2] = r;
	data->img.data[pos + 3] = 0xff;
}

void	set_instructions(t_frctl *data)
{
	char	*str;
	int		i;
	int		c;

	i = 0;
	c = 0xffD0ff;
	while (i++ < data->width)
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, i, data->height, 0xFFFFFF);
	str = "USAGE:";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, data->height + 20, c, str);
	str = "wheel    ZOOM IN/OUT";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, data->height + 50, c, str);
	str = "arrows   MOOVE";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, data->height + 65, c, str);
	str = "<>/      COLOR SET";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, data->height + 80, c, str);
	str = "esc      EXIT";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, data->height + 95, c, str);
	if (data->type == 1 || data->type == 2)
		str = data->type == 1 ? "mandelbrot" : "julia";
	else
		str = "newthon";
	mlx_string_put(data->mlx_ptr, data->win_ptr, (data->width / 2) - 30,\
		data->height + 12, 0xffD0ff, str);
	str = NULL;
}

void	print_pallete(t_frctl *data)
{
	int i;
	int h;
	int hex;
	int it;

	it = data->iter / 100;
	i = 0;
	while (i < 100)
	{
		it = data->iter / 100 * i;
		h = data->height + 30;
		hex = (data->color.pallete[0][it] << 16 |\
			data->color.pallete[1][it] << 8 | data->color.pallete[2][it]);
		while (h++ < data->height + 45)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr,\
				data->width - 127 + i, h, hex);
		i++;
	}
}

void	set_color_info(t_frctl *data)
{
	char	*str;

	str = "PALLETTE:";
	put_str(data, 100, 20, str);
	str = get_string("r1: ", data->color.pallete[0][1]);
	put_str(data, 150, 60, str);
	free(str);
	str = get_string("g1: ", data->color.pallete[1][1]);
	put_str(data, 150, 75, str);
	free(str);
	str = get_string("b1: ", data->color.pallete[2][1]);
	put_str(data, 150, 90, str);
	free(str);
	str = get_string("r2: ", data->color.pallete[0][(int)data->iter]);
	put_str(data, 50, 60, str);
	free(str);
	str = get_string("g2: ", data->color.pallete[1][(int)data->iter]);
	put_str(data, 50, 75, str);
	free(str);
	str = get_string("b2: ", data->color.pallete[2][(int)data->iter]);
	put_str(data, 50, 90, str);
	free(str);
}
