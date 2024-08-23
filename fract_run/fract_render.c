/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:49:30 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/21 00:34:21 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"


void	put_pixel(int x, int y, t_image *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bits_per_pixel) / 8);
	*((unsigned int *)(img->addr + offset)) = color;
}

//JULIA
// params = {real , i}
// z = pixel point + c
// Transform arg to double

//mandelbrot
//z = z^2 + x
// z is initially (0,0)
// c is the actual point
// We put pixels OUTSIDE mandelbrot set
void	handle_coordinate(int x, int y, t_fract *fract)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			colored_px;

	i = 0;
	z.x = 0.0;
	z.y = 0.0;
	c.x = (fract->scale * linear_interpol(x, -2, 2, WIDTH)) + fract->shift_x;
	c.y = (fract->scale * linear_interpol(y, 2, -2, HEIGHT)) + fract->shift_y;

	colored_px = BLACK;
	//printf("sqr -> c.x = %f \t c.y = %f\n", c.x, c.y);
	while (i < fract->iter_definition)
	{
		//z = z^2 + c --> mandelbrot
		z = square_z(z);
		z = sum_z(z, c);

		// the value escaped --> if hypotenuse > 2 => point escaped (c = sqr(a² + b²))
		if ((z.x * z.x) + (z.y * z.y) > fract->escape_val)
		{
			colored_px = linear_interpol(i, GRAY, WHITE, fract->iter_definition);
			put_pixel(x, y, &fract->image, colored_px);
			return ;
		}
		i++;
	}
	put_pixel(x, y, &fract->image, WHITE);
}
//c.y = linear_interpol (y, -2, 2, HEIGHT); should normaly reverse -2 and +2
// so it reverse it and while start at the right top corner of the window
// ==> c.y = linear_interpol (y, 2, -2, HEIGHT);


void	fractol_render(t_fract *fract)
{
	int	x;
	int	y;
	int	img_offset;
	int	step;

	step = 4;
	img_offset = 0;
	while (img_offset < step)
	{
		y = 0;
		while (y < HEIGHT)
		{
			x = img_offset;
			while (x < WIDTH)
			{

				handle_coordinate(x, y, fract);
				x += step;

			}
			y += 1;
		}
		ft_printf("img offeset %i --> DONE \n", img_offset);
		mlx_put_image_to_window(fract->mlx_connexion, fract->mlx_window,
			fract->image.img, 0, 0);
		img_offset++;
	}
}
