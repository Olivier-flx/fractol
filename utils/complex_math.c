/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 00:26:25 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/24 12:56:40 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

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

// (4 + 2i) x (3 - 8i) = (4 * 3) + (-4 * 8i) + (2i * 3) - (2i * 8i)
// (4 + 2i) x (3 - 8i) = 12 - 32i + 6i - 16i^2
// (4 + 2i) x (3 - 8i) = 12 - 26i + 16
// (4 + 2i) x (3 - 8i) = 28 - 26i
t_complex	multiply_z(t_complex a, t_complex b)
{
	t_complex	ret_val;

	ret_val.x = a.x * b.x - a.y * b.y;
	ret_val.y = a.x * b.y + a.y * b.x;
	return (ret_val);
}

// (4 + 2i) / (3 - 8i) =  ((4 + 2i) * (3 + 8i)) / ((3 - 8i) * (3 + 8i))
// (4 + 2i) / (3 - 8i) =  ((12 + 38i + (-16))) / (( 9 + 24i - 24i - (-64)))
// (4 + 2i) / (3 - 8i) = (-4 + 38i) / 73
// (4 + 2i) / (3 - 8i) = -4/73 + 38i/73
t_complex	divide_z(t_complex a, t_complex b)
{
	t_complex	ret_val;
	double		conjugate_denom;

	conjugate_denom = b.x * b.x + b.y * b.y;
	ret_val.x = (a.x * b.x + a.y * b.y) / conjugate_denom;
	ret_val.y = (a.x * b.y - a.y * b.x) / conjugate_denom;
	return (ret_val);
}

t_complex	sum_z(t_complex z1, t_complex z2)
{
	t_complex	ret_val;

	ret_val.x = z1.x + z2.x;
	ret_val.y = z1.y + z2.y;
	return (ret_val);
}

t_complex	substracte_z(t_complex z1, t_complex z2)
{
	t_complex	ret_val;

	ret_val.x = z1.x - z2.x;
	ret_val.y = z1.y - z2.y;
	return (ret_val);
}
