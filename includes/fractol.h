/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <sisidra@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 01:10:05 by sisidra           #+#    #+#             */
/*   Updated: 2020/07/14 01:10:05 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "mlx.h"
# include <math.h>
# include "../libft/libft.h"
# include <pthread.h>

typedef struct		s_complex
{
	double			re;
	double			im;
}					t_complex;

typedef struct		s_color
{

	int				rgb;
	int				srgb;
	int				pallete[3][255];
	int				col_switch;
	float			scolr;
	float			step_r;
	float			step_g;
	float			step_b;
	float			step;
}					t_color;

typedef struct		s_image
{
	char			*data;
	int				size;
	int				endian;
	int				bpp;
}					t_image;

typedef struct		s_frctl
{
	double			x;
	double			y;
	double			mx;
	double			my;
	t_complex		z;
	t_complex		z0;
	int				c;
	int				type;
	int				width;
	int				height;
	int				rays;
	double			delta_x;
	double			delta_y;
	double			m_x;
	double			m_y;
	double			zoom;
	float			iter;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	t_image			img;
	t_color			color;
	int				is_default;
	int				tread[4];
}					t_frctl;

t_complex			c_add(t_complex a, t_complex b);
t_complex			c_sub(t_complex a, t_complex b);
t_complex			c_sqr(t_complex a);
t_complex			c_pow(t_complex a, int pow);
t_complex			c_set(double a, double b);
double				c_arg(t_complex a);
double				c_mod(t_complex a);
void				step_count(t_color *color, float iter);
void				ft_close(t_frctl *data, int status);
void				mandelbrot(t_frctl *data, int pos, double x, double y);
void				julia(t_frctl *data, int pos, int x, int y);
void				newthon(t_frctl *data, int pos, double x, double y);
void				julia_set(t_frctl *data);
void				mandelset(t_frctl *data);
void				newthon_set(t_frctl *data);
void				fractol(t_frctl *data, int pos, int x, int y);
void				block(t_frctl *data);
void				set_default(t_frctl *data, char *type);
void				set_instructions(t_frctl *data);
void				set_pallette(t_color *color, int iter);
void				print_pallete(t_frctl *data);
void				get_color(t_frctl *data, t_color *color, int iter, int pos);
void				set_color_info(t_frctl *data);
void				treads(t_frctl *data);
char				*get_string(char *str, int num);
void				put_str(t_frctl *data, int x, int y, char *str);
int					key_def(int key, t_frctl *data);
int					mouse_hook(int mousecode, int x, int y, t_frctl *data);
int					mouse_moove(int x, int y, t_frctl *data);
#endif
