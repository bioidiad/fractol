/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <sisidra@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 00:25:30 by sisidra           #+#    #+#             */
/*   Updated: 2020/07/14 00:25:30 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_complex	c_add(t_complex a, t_complex b)
{
	t_complex c;

	c.re = a.re + b.re;
	c.im = a.im + b.im;
	return (c);
}

t_complex	c_sub(t_complex a, t_complex b)
{
	t_complex c;

	c.re = a.re - b.re;
	c.im = a.im - b.im;
	return (c);
}

t_complex	c_sqr(t_complex a)
{
	t_complex c;

	c.re = a.re * a.re - a.im * a.im;
	c.im = 2 * a.re * a.im;
	return (c);
}

t_complex	c_pow(t_complex a, int n)
{
	t_complex	res;
	double		arg;
	double		mod;

	arg = c_arg(a);
	mod = c_mod(a);
	res.re = pow(mod, n) * cos(arg * n);
	res.im = pow(mod, n) * sin(arg * n);
	return (res);
}

t_complex	c_set(double a, double b)
{
	t_complex	res;

	if (!a)
		a = 0.0;
	if (!b)
		b = 0.0;
	res.re = a;
	res.im = b;
	return (res);
}
