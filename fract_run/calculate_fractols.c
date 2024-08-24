/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_fractols.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:40:30 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/24 02:08:43 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

//////  MANDELBROT  //////
//z = z^2 + x
// z is initially (0,0)
// c is the actual point
// We put pixels OUTSIDE mandelbrot set
// the value escaped --> if hypotenuse > 2 => point escaped (c = sqr(a² + b²))
//		(z.x * z.x) + (z.y * z.y) > fract->escape_val

void	calculate_mandelbrot(int x, int y, t_fract *fra)
{
	t_complex	z;
	int			i;
	int			colored_px;

	i = 0;
	z.x = 0.0;
	z.y = 0.0;
	fra->c.x = (fra->scale * lin_interpol(x, -2, 2, WIDTH)) + fra->shift_x;
	fra->c.y = (fra->scale * lin_interpol(y, 2, -2, HEIGHT)) + fra->shift_y;
	//printf("sqr -> c.x = %f \t c.y = %f\n", c.x, c.y);
	while (i < fra->iter_definition)
	{
		z = square_z(z);
		z = sum_z(z, fra->c);
		if ((z.x * z.x) + (z.y * z.y) > fra->escape_val)
		{
			//colored_px = interpolate_color(LIGHT_BLUE,NEON_BLUE , fra->iter_definition / ((1 + i) * 10));
			colored_px = lin_interpol(i, WHITE, BLACK, fra->iter_definition);
			put_pixel(x, y, &fra->image, colored_px);
			return ;
		}
		i++;
	}
	put_pixel(x, y, &fra->image, WHITE);
}

//////  JULIA  //////
// params = {real , i}
// z = pixel point + const
// Transform arg to double
void	calculate_julia(int x, int y, t_fract *fract)
{
	t_complex	z;

	int			i;
	int			colored_px;
	i = 0;
	z.x = (fract->scale * lin_interpol(x, -2, 2, WIDTH)) + fract->shift_x;
	z.y = (fract->scale * lin_interpol(y, 2, -2, HEIGHT)) + fract->shift_y;
	colored_px = BLACK;
	//printf("sqr -> c.x = %f \t c.y = %f\n", c.x, c.y);
	while (i < fract->iter_definition)
	{
		//z = z^2 + c --> mandelbrot
		z = square_z(z);
		z = sum_z(z, fract->c);
		// the value escaped --> if hypotenuse > 2 => point escaped (c = sqr(a² + b²))
		if ((z.x * z.x) + (z.y * z.y) > fract->escape_val)
		{
			//colored_px = interpolate_color(LIGHT_BLUE,NEON_BLUE , fract->iter_definition / ((1 + i) * 10));
			colored_px = lin_interpol(i, WHITE, BLACK, fract->iter_definition);
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

////// NEWTON /////////
// f(z) = z^3 − 1
// zn+1 = z - R * (f(zn) / f'(zn))
// R is beetween [0.2,2.2]
// f(z_{n->infty}) = 0  every point converges to a root of the complex function
// f'(zn) = 3z^2

t_complex	f_z(t_complex z)
{
	t_complex	c;

	c.x = -1;
	c.y = 0;
	z = multiply_z(square_z(z), z);
	z = sum_z(z, c);
	return (z);
}

t_complex	f_prime_z(t_complex z)
{
	t_complex tmp;

	tmp = square_z(z);
	z.x = 3 * tmp.x;
	z.y = 3 * tmp.y;
	return (z);
}

t_complex	f_zn_plus_1(t_complex z_n, t_complex z, t_complex f_z_prime)
{
	t_complex	zn_plus_1;
	t_complex	result_div;

	result_div = divide_z(z, f_z_prime);
	zn_plus_1.x = z_n.x - result_div.x;
	zn_plus_1.y = z_n.y - result_div.y;
	return (zn_plus_1);
}

void	calculate_newton(int x, int y, t_fract *fract)
{
	t_complex	z;
	t_complex	z_n;
	t_complex	f_z_prime;
	t_complex	zn_plus_1;
	t_complex	dif_zn1_zn;
	double		tolerance;
	int			i;
	int			color;

	i = 0;
	z.x = (fract->scale * lin_interpol(x, -2, 2, WIDTH)) + fract->shift_x;
	z.y = (fract->scale * lin_interpol(y, 2, -2, HEIGHT)) + fract->shift_y;
	tolerance = 1;
	while (i < 100/*fract->iter_definition*/)
	{
		z_n = z;
		z = f_z(z);
		f_z_prime = f_prime_z(z_n);
		zn_plus_1 = f_zn_plus_1(z_n, z, f_z_prime);
		dif_zn1_zn.x = zn_plus_1.x - z_n.x;
		dif_zn1_zn.y = zn_plus_1.y - z_n.y;
		if ((dif_zn1_zn.x * dif_zn1_zn.x) + (dif_zn1_zn.y * dif_zn1_zn.y) \
		< tolerance)
			break ;
		z = zn_plus_1;
		i++;
	}
//	double modulus = sqrt(z.x * z.x + z.y * z.y);
	if (fabs(z.x - 1) < tolerance && fabs(z.y) < tolerance * tolerance)
		color = RED;
	else if (fabs(z.x + 0.5) < tolerance && fabs(z.y - sqrt(3)/2) < tolerance)
		color = GREEN;
	else if (fabs(z.x + 0.5) < tolerance && fabs(z.y + sqrt(3)/2) < tolerance)
		color = BLUE;
	else
		color = WHITE;

	put_pixel(x, y, &fract->image, color);
}
