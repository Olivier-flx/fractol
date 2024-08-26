/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_fractols.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:40:30 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/26 19:50:42 by ofilloux         ###   ########.fr       */
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
	while (i < fra->iter_definition)
	{
		z = square_z(z);
		z = sum_z(z, fra->c);
		if ((z.x * z.x) + (z.y * z.y) > fra->escape_val)
		{
			colored_px = lin_interpol(i, BLUE, NEON_TURQUOISE, \
				fra->iter_definition * 100);
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
// https://www.rapidtables.com/convert/number/hex-to-decimal.html?x=E5E5FF
void	calculate_julia(int x, int y, t_fract *fract)
{
	t_complex	z;
	int			i;
	int			colored_px;

	i = 0;
	z.x = (fract->scale * lin_interpol(x, -2, 2, WIDTH)) + fract->shift_x;
	z.y = (fract->scale * lin_interpol(y, 2, -2, HEIGHT)) + fract->shift_y;
	colored_px = BLACK;
	while (i < fract->iter_definition)
	{
		z = square_z(z);
		z = sum_z(z, fract->c);
		if ((z.x * z.x) + (z.y * z.y) > fract->escape_val)
		{
			colored_px = lin_interpol(i, 15066623, 255, fract->iter_definition);
			put_pixel(x, y, &fract->image, colored_px);
			return ;
		}
		i++;
	}
	put_pixel(x, y, &fract->image, BLACK);
}
//c.y = linear_interpol (y, -2, 2, HEIGHT); should normaly reverse -2 and +2
// so it reverse it and while start at the right top corner of the window
// ==> c.y = linear_interpol (y, 2, -2, HEIGHT);

////// BURNING SHIP ////////
//zn+1​ =( ∣Re(zn)∣ + i∣Im(zn) ∣ )^2 +c
void	calculate_burning_ship(int x, int y, t_fract *fra)
{
	t_complex	z;
	t_complex	zn1;
	t_complex	c;
	int			i;
	int			colored_px;

	i = 0;
	z.x = 0.0;
	z.y = 0.0;
	c.x = (fra->scale * lin_interpol(x, -2, 2, WIDTH)) + fra->shift_x;
	c.y = (fra->scale * lin_interpol(y, 2, -2, HEIGHT)) + fra->shift_y;
	while (i < fra->iter_definition)
	{
		zn1 = sum_z(square_z(create_complex(fabs(z.x), fabs(z.y))), c);
		if ((z.x * z.x) + (z.y * z.y) > fra->escape_val)
		{
			colored_px = lin_interpol(i, WHITE, BLUE, fra->iter_definition);
			put_pixel(x, y, &fra->image, colored_px);
			return ;
		}
		z = zn1;
		i++;
	}
	put_pixel(x, y, &fra->image, BLACK);
}

void	calculate_mandelbar(int x, int y, t_fract *fra)
{
	t_complex	z;
	t_complex	c;
	double		temp;
	int			i;
	int			colored_px;

	i = 0;
	z.x = 0.0;
	z.y = 0.0;
	c.x = (fra->scale * lin_interpol(x, -2, 2, WIDTH)) + fra->shift_x;
	c.y = (fra->scale * lin_interpol(y, 2, -2, HEIGHT)) + fra->shift_y;
	while (i < fra->iter_definition)
	{
		temp = (z.x * z.x) - (z.y * z.y) + c.x;
		z.y = (-2.0 * z.x * z.y) + c.y;
		z.x = temp;
		if ((z.x * z.x) + (z.y * z.y) > fra->escape_val)
		{
			colored_px = lin_interpol(i, WHITE, BLUE, fra->iter_definition / 2);
			put_pixel(x, y, &fra->image, colored_px);
			return ;
		}
		i++;
	}
	put_pixel(x, y, &fra->image, BLACK);
}


////// NEWTON /////////
// f(z) = z^3 − 1
// zn+1 = z - R * (f(zn) / f'(zn))
// R is beetween [0.2,2.2]
// f(z_{n->infty}) = 0  every point converges to a root of the complex function
// f'(zn) = 3z^2
//calculer la différence entre zn et zn+1 est une partie importante
//du processus de la méthode de Newton pour vérifier la convergence.
void	calculate_newton(int x, int y, t_fract *fract)
{
	t_complex	z;
	t_complex	zn;
	t_complex	z_n1;
	int			i;

	i = 0;
	z.x = (fract->scale * lin_interpol(x, -2, 2, WIDTH)) + fract->shift_x;
	z.y = (fract->scale * lin_interpol(y, 2, -2, HEIGHT)) + fract->shift_y;
	zn = z;
	while (i < fract->iter_definition)
	{
		if (is_tolerance_ok(fract, zn) == 1)
			return (put_pixel(x, y, &fract->image, fract->color));
		z_n1 = newton_iteration(zn);
		zn = z_n1;
		i++;
	}
	put_pixel(x, y, &fract->image, WHITE);
}

///// NEXT STEP NOVA FRACTAL /////////
/// https://rotgers.io/posts/nova-fractals/
/*
t_complex nova_iter(t_complex zn)
{
	t_complex zn1;

	zn1 = sum_z(
			substracte_z(
				zn,
				divide_z(
				substracte_z(multiply_z(square_z(zn),zn)
				,create_compl(10)),multiply_z(square_z(zn)
				create_complex(3,0))))
		,create_complex(1,0));
	return (zn1);
}

void	calculate_nova(int x, int y, t_fract *fract)
{
	t_complex	z;
	t_complex	zn;
	t_complex	z_n1;
	int			i;

	i = 0;
	z.x = (fract->scale * lin_interpol(x, -2, 2, WIDTH)) + fract->shift_x;
	z.y = (fract->scale * lin_interpol(y, 2, -2, HEIGHT)) + fract->shift_y;
	zn = z;
	while (i < fract->iter_definition)
	{
		if (is_tolerance_ok(fract, zn) == 1)
			return (put_pixel(x, y, &fract->image, fract->color));
		z_n1 = nova_iter(create_complex(1,0));
		zn = z_n1;
		i++;
	}
	put_pixel(x, y, &fract->image, WHITE);
}
*/

/*  newton test
//calculer la différence entre zn et zn+1 est une partie importante
 //du processus de la méthode de Newton pour vérifier la convergence.
void	calculate_newton(int x, int y, t_fract *fract)
{
	t_complex	z;
	t_complex	z_n;
	t_complex	f_z_prime;
	t_complex	zn_plus_1;
	t_complex	dif_zn1_zn;
	int			i;
	int			color;

	i = 0;
	z.x = ((fract->scale * lin_interpol(x, -2, 2, WIDTH)) + fract->shift_x);
	z.y = ((fract->scale * lin_interpol(y, 2, -2, HEIGHT)) + fract->shift_y);
	z_n = z;
	while (i < 1000)
	{
		z = f_z(z);
		f_z_prime = f_prime_z(z_n);
		zn_plus_1 = f_zn_plus_1(z_n, z, f_z_prime);
		dif_zn1_zn = substracte_z(zn_plus_1, z_n);
		if (fabs(z.y) > 10000000 || fabs(z.x) > 10000000)
			break;
		if (fabs((dif_zn1_zn.x * dif_zn1_zn.x) + (dif_zn1_zn.y * dif_zn1_zn.y)) \
		< TOLERANCE * TOLERANCE)
			break ;
				z = zn_plus_1;
		i++;
	}
//	double modulus = sqrt(z.x * z.x + z.y * z.y);
	if (fabs(z.x - 1) < TOLERANCE && fabs(z.y) < TOLERANCE)
		color = RED;
	else if (fabs(z.x - 0.5) < TOLERANCE && fabs(z.y + sqrt(3)/2) < TOLERANCE)
		color = GREEN;
	else if (fabs(z.x - 0.5) < TOLERANCE && fabs(z.y - sqrt(3)/2) < TOLERANCE)
		color = BLUE;
	else
		color = WHITE;

	put_pixel(x, y, &fract->image, color);
}
*/
