#include "fractol.h"

int     get_color(t_frctl *data, int iter)
{
    int r;
    int g;
    int b;
    double c;
    if (iter >= 1000)
        return (0x000000);
    c = iter + (0.326634259978281 - log(log(mod(data->z0))) / log(2));
    // if (c > 25)
    //     printf("c = %f\n", c);
    r = 0;
    g = 0;
    b = 0;
    iter = c;
    b += (iter);
    if (b > 255)
    {
        g += b - 255;
        b = 255;
        if (g > 255)
        {
            r += g - 255;
            g = 255;
            if (r > 255)
                r = 255;
        } 
    }

    // if (r <= 255 && g < 100 && b < 17)
    //     return (0xFF3030);
    
    //return (0xFFFFFF);
    
    
    return (r << 16 | g << 8 | b << 0);
}
void    draw(t_frctl *data)
{
    while (data->y <= data->height)
    {
        data->x = 0;
        while (data->x <= data->width)
        {
            data->z0.re = 0;
            data->z0.im = 0;
            iterfract(data);
            data->x++;
        }
        data->y++;
    }
    data->x = 0;
    data->y = 0;
}

int key_def(int key, t_frctl *data)
{
    if (key == 65307)
        exit(0);
    else if (key == 105)
        data->zoom += 150;
    else if (key == 111)
        data->zoom -= 150;
    else if (key == 65363)
        data->delta_x += 100;
    else if (key == 65361)
        data->delta_x -= 100;
    else if (key == 65362)
        data->delta_y -= 100;
    else if (key == 65364)
        data->delta_y += 100;
    else
        return (0);
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw(data);
	return (0);
}

void	set_default(t_frctl *data)
{
	data->width = 500;
    data->height = 500;
    data->zoom = (data->width * data->height) * 0.0005;
    data->delta_x = data->width * 0.75;
    data->delta_y = data->height / 2;	
	data->is_default = 1;
}

int     main(void)
{
    t_frctl *data;
    data = (t_frctl*)malloc(sizeof(t_frctl));
    if (data->is_default != 1)
        set_default(data);    
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->width, data->height, "fractol");
	draw(data);
	mlx_key_hook(data->win_ptr, key_def, data);
	mlx_loop(data->mlx_ptr);
}