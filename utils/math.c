/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:14:22 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/23 15:01:22 by ofilloux         ###   ########.fr       */
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

/* NO USED */
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

double	ft_atof(char *s)
{
	int		i;
	double	tmp;
	double	n;
	int		sign;

	i = 0;
	tmp = 1;
	sign = 1;
	n = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	while (s[i] == '-' || s[i] == '+')
		if(s[i++] == '-')
			sign *= -1;
	if (s[i] < '0' && s[i] > '9')
		return ((double) wrong_params_float());
	while (s[i] >= '0' && s[i] <= '9')
		n = n * 10 + (double)(s[i++] - 48);
	if (s[i++] == '.')
		while (s[i] >= '0' && s[i] <= '9')
		{
			tmp = tmp * 10;
			n = n + (double)(s[i++] - 48) / tmp;
		}
	else if (s[i] == ',')
		wrong_params_float();
	return (n * (double)sign);
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
