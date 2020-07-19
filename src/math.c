/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <sisidra@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 02:09:02 by sisidra           #+#    #+#             */
/*   Updated: 2020/07/14 02:09:02 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

double	c_arg(t_complex a)
{
	double	arg;
	double	pi;

	pi = 3.1415926535;
	if (a.re < 0 && a.im > 0)
		arg = pi + atan(a.im / a.re);
	else if (a.re < 0 && a.im < 0)
		arg = -pi + atan(a.im / a.re);
	else
		arg = atan(a.im / a.re);
	return (arg);
}

double	c_mod(t_complex a)
{
	return (sqrt(a.re * a.re + a.im * a.im));
}

void	step_count(t_color *color, float iter)
{
	color->step_r = ((color->rgb >> 16 & 0xFF) - \
		(color->srgb >> 16 & 0xFF)) / iter;
	color->step_g = ((color->rgb >> 8 & 0xFF) - \
		(color->srgb >> 8 & 0xFF)) / iter;
	color->step_b = ((color->rgb >> 0 & 0xFF) - \
		(color->srgb >> 0 & 0xFF)) / iter;
	if (color->step_r < 0.0)
		color->step_r *= -1.0;
	if (color->step_g < 0.0)
		color->step_g *= -1.0;
	if (color->step_b < 0.0)
		color->step_b *= -1.0;
}

char	*get_string(char *str, int num)
{
	char *tmp;

	tmp = ft_itoa(num);
	str = ft_strjoin(str, tmp);
	free(tmp);
	return (str);
}

void	put_str(t_frctl *data, int x, int y, char *str)
{
	int c;

	x = data->width - x;
	y = data->height + y;
	c = 0xffD0ff;
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, c, str);
}
