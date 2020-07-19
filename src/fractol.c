/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <sisidra@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 00:36:10 by sisidra           #+#    #+#             */
/*   Updated: 2020/07/14 00:36:10 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	fractol(t_frctl *data, int pos, int x, int y)
{
	if (data->type == 1)
		mandelbrot(data, pos, (double)x, (double)y);
	else if (data->type == 2)
		julia(data, pos, x, y);
	else if (data->type == 3)
		newthon(data, pos, (double)x, (double)y);
}

void	mandelbrot(t_frctl *data, int pos, double x, double y)
{
	int			i;
	t_complex	c;
	t_complex	z0;

	i = 0;
	z0 = c_set(0, 0);
	while (++i < data->iter && c_mod(z0) <= 2)
	{
		c.re = ((x - data->delta_x + data->m_x) / data->zoom);
		c.im = ((y - data->delta_y + data->m_y) / data->zoom);
		z0 = c_add(c_sqr(z0), c);
	}
	get_color(data, &data->color, i, pos);
}

void	julia(t_frctl *data, int pos, int x, int y)
{
	t_complex	a;
	t_complex	c;
	t_complex	ab;
	float		twoab;
	int			n;

	c = c_set(data->mx, data->my);
	a.re = (x - data->width / 2) / (data->width / 0.3) * data->zoom;
	a.im = (y - data->height / 2) / (data->height / 0.3) * data->zoom;
	n = 0;
	while (n < data->iter)
	{
		ab.re = a.re * a.re;
		ab.im = a.im * a.im;
		if (ab.re + ab.im > 4.0)
			break ;
		twoab = 2.0 * a.re * a.im;
		a.re = ab.re - ab.im + c.re;
		a.im = twoab + c.im;
		n++;
	}
	get_color(data, &data->color, n, pos);
}

void	newthon(t_frctl *data, int pos, double x, double y)
{
	t_complex	z0;
	t_complex	temp;
	t_complex	z1;
	int			i;

	x = (x - (data->delta_x)) * data->zoom;
	y = (y - (data->delta_y)) * data->zoom;
	z0 = c_set(x, y);
	temp = c_set(0, 0);
	i = 0;
	if (x || y)
	{
		while (c_mod(c_sub(z0, temp)) >= data->zoom)
		{
			temp = z0;
			z1 = c_pow(z0, data->rays);
			z1 = c_set(0.2 * z1.re, 0.2 * z1.im);
			z0 = c_set(0.8 * z0.re, 0.8 * z0.im);
			z0 = c_add(z0, z1);
			i++;
		}
	}
	get_color(data, &data->color, i, pos);
}
