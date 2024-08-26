/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:45:15 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/26 15:52:34 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

t_complex	f_z(t_complex z)
{
	t_complex	c;

	c.x = 1;
	c.y = 0;
	z = multiply_z(square_z(z), z);
	z = substracte_z(z, c);
	return (z);
}

t_complex	f_prime_z(t_complex z)
{
	t_complex	tmp;
	t_complex	trois_zero;

	trois_zero.x = 3;
	trois_zero.y = 0;
	tmp = square_z(z);
	z = multiply_z(tmp, trois_zero);
	return (z);
}

t_complex	f_zn_plus_1(t_complex z_n, t_complex z, t_complex f_z_prime)
{
	t_complex	zn_plus_1;
	t_complex	result_div;

	result_div = divide_z(z, f_z_prime);
	zn_plus_1 = substracte_z(z_n, result_div);
	return (zn_plus_1);
}

t_complex	newton_iteration(t_complex zn)
{
	t_complex zn1;

	zn1 = substracte_z(zn, divide_z(f_z(zn), f_prime_z(zn)));
	return (zn1);
}

int	is_tolerance_ok(t_fract *fract, t_complex zn1)
{
	t_complex distance;
	double dist_euclidienne;

	distance = substracte_z(zn1, create_complex(1, 0));
	dist_euclidienne = pow(distance.x, 2) + pow(distance.y, 2);
	if (pow(distance.x, 2) < TOLERANCE && pow(distance.y, 2) < TOLERANCE)
		return (fract->color = RED, 1);
	distance = substracte_z(zn1, create_complex(-0.5, sqrt(3)/2));
	dist_euclidienne = pow(distance.x, 2) + pow(distance.y, 2);
	if (dist_euclidienne < TOLERANCE)
		return (fract->color = GREEN, 1);
	distance = substracte_z(zn1, create_complex(-0.5, -sqrt(3)/2));
	dist_euclidienne = pow(distance.x, 2) + pow(distance.y, 2);
	if (dist_euclidienne < TOLERANCE)
		return (fract->color = BLUE, 1);
	return (0);
}
