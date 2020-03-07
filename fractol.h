#ifndef FRACTOL_H
# define FRACTOL_H
# include "mlx.h"
# include <math.h>
# include "libft/libft.h"

typedef struct 
{
    double re;
    double im;   
} complex;

typedef struct
{
    float x;
    float y;
    complex z;
    complex z0;
    int c;
    int width;
    int height;
    int delta_x;
    int delta_y;
    int zoom;
    void *mlx_ptr;
    void *win_ptr;
    int is_default;
} t_frctl;

complex add(complex a,complex b);
complex sqr(complex a);
double mod(complex a);
void iterfract(t_frctl *data);
int     get_color(t_frctl *data, int iter);
complex mapPoint(int width,int height,double radius,int x,int y);
#endif