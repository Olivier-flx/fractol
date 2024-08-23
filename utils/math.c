/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:14:22 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/21 00:32:41 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

//double linear_interpolation(double x, double new_min, double new_max,
//								double min, double max)
//f_x = ((new_max - new_min) * (x - min) / (max - min)) + new_min;
// min = 0 ; max = width
double	linear_interpol(double x, double new_min, double new_max, double max)
{
	double	old_min;
	double range_old;
	double range_new;
	double	f_x;

	old_min = 0;
	range_old = max - old_min;
	range_new = new_max - new_min;
	f_x = ((range_new) * (x - old_min) / range_old) + new_min;
	return (f_x);
}

double	rev_linear_interpol(double x, double new_min, double new_max, double max)
{
	double	old_min;
	double range_old;
	double range_new;
	double	f_x;

	old_min = -2;
	range_old = max - old_min;
	range_new = new_max - new_min;
	f_x = ((range_new) * (x - old_min) / range_old) + new_min;
	return (f_x);
}

// (x + yi)²
// x² + 2yxi + yi²
// x² + 2yxi - y²
// (x² - y²) + 2xyi // -->reel part on left, imaginary part on right
t_complex	square_z(t_complex z)
{
	t_complex	ret_val;

	ret_val.x = (z.x * z.x) - (z.y * z.y);
	ret_val.y = 2 * z.x * z.y;
	return (ret_val);
}

inline t_complex	sum_z(t_complex z1, t_complex z2)
{
	t_complex	ret_val;

	ret_val.x = z1.x + z2.x;
	ret_val.y = z1.y + z2.y;
	return (ret_val);
}
