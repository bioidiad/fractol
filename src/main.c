/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisidra <sisidra@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 01:53:29 by sisidra           #+#    #+#             */
/*   Updated: 2020/07/14 01:53:29 by sisidra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int		*position(t_frctl *data)
{
	int	*pos;

	pos = (int*)malloc(sizeof(int) * 4);
	pos[0] = 0;
	pos[1] = data->width * 2;
	pos[2] = pos[1] * data->height;
	pos[3] = pos[2] + data->width * 2;
	return (pos);
}

void	iterate(t_frctl *data, int *xysxsy, int *pos, int i)
{
	while (xysxsy[1] < (data->height / 2) + xysxsy[3])
	{
		xysxsy[0] = xysxsy[2];
		while (xysxsy[0] < (data->width / 2) + xysxsy[2])
		{
			fractol(data, pos[i], xysxsy[0], xysxsy[1]);
			pos[i] += 4;
			xysxsy[0]++;
		}
		pos[i] += data->width * 2;
		xysxsy[1]++;
	}
}

void	*draw(void *datas)
{
	int			*pos;
	int			xysxsy[4];
	int			i;
	t_frctl		*data;

	data = (t_frctl*)datas;
	i = 0;
	while (data->tread[i] != 0 && i < 4)
		i++;
	data->tread[i] = 1;
	xysxsy[0] = (i == 0 || i == 2) ? 0 : data->width / 2;
	xysxsy[1] = i <= 1 ? 0 : data->height / 2;
	xysxsy[2] = xysxsy[0];
	xysxsy[3] = xysxsy[1];
	pos = position(data);
	if (data->type != 2)
		set_pallette(&data->color, data->iter);
	iterate(data, xysxsy, pos, i);
	free(pos);
	pthread_exit(0);
}

void	treads(t_frctl *data)
{
	int			i;
	pthread_t	one;
	pthread_t	two;
	pthread_t	three;
	pthread_t	four;

	i = 0;
	while (i < 4)
		data->tread[i++] = 0;
	pthread_create(&one, NULL, draw, data);
	pthread_create(&two, NULL, draw, data);
	pthread_create(&three, NULL, draw, data);
	pthread_create(&four, NULL, draw, data);
	pthread_join(one, NULL);
	pthread_join(two, NULL);
	pthread_join(three, NULL);
	pthread_join(four, NULL);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	set_instructions(data);
	set_color_info(data);
	print_pallete(data);
}

int		main(int argc, char **argv)
{
	t_frctl	*data;

	data = (t_frctl*)malloc(sizeof(t_frctl));
	if (argc != 2)
		ft_close(data, -1);
	else
		data->is_default = 0;
	if (!data->is_default)
		set_default(data, argv[1]);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->width,\
		data->height + 100, "fractol");
	data->img_ptr = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->img.data = mlx_get_data_addr(data->img_ptr, &data->img.bpp,\
		&data->img.size, &data->img.endian);
	treads(data);
	mlx_key_hook(data->win_ptr, key_def, data);
	if (data->type == 2)
		mlx_hook(data->win_ptr, 6, 1L << 6, mouse_moove, data);
	mlx_mouse_hook(data->win_ptr, mouse_hook, data);
	mlx_loop(data->mlx_ptr);
}
