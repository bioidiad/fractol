#include "fractol.h"

complex add(complex a,complex b)
{
	complex c;
	c.re = a.re + b.re;
	c.im = a.im + b.im;
	return c;
}
 
complex sqr(complex a)
{
	complex c;
	c.re = a.re*a.re - a.im*a.im;
	c.im = 2*a.re*a.im;
	return c;
}
 
double mod(complex a)
{
	return sqrt(a.re*a.re + a.im*a.im);
}
 
complex mapPoint(int width,int height,double radius,int x,int y)
{
	complex c;
	int l = (width<height)?width:height;
 
	c.re = 2*(x - width/2.0)/l;
	c.im = 2*(y - height/2.0)/l;
 
	return c;
}
void	iterfract(t_frctl *data)
{
	complex c;
	int i;
	i = 0;
	while(i < 1000 && mod(data->z0) <= 2)
	{
		c.re = (data->x - (data->delta_x)) / data->zoom;
		c.im = (data->y - data->delta_y) / data->zoom;
		data->z0 = add(sqr(data->z0),c);
		++i;
	}
		//printf("z = %f\n", data->z0.re);
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int)data->x, (int)data->y, get_color(data, i));

}