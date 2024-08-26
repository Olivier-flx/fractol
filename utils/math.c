/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:14:22 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/26 21:31:47 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

//double linear_interpolation(double x, double new_min, double new_max,
//								double min, double max)
//f_x = ((new_max - new_min) * (x - min) / (max - min)) + new_min;
// min = 0 ; max = width
double	lin_interpol(double x, double start, double end, double screen_size)
{
	double	screen_size_start;
	double	range_old;
	double	range_new;
	double	f_x;

	screen_size_start = 0;
	range_old = screen_size - screen_size_start;
	range_new = end - start;
	f_x = ((range_new) * (x - screen_size_start) / range_old) + start;
	return (f_x);
}

/* NO USED */
double	rev_lin_interpol(double x, double new_min, double new_max, double max)
{
	double	old_min;
	double	range_old;
	double	range_new;
	double	f_x;

	old_min = -2;
	range_old = max - old_min;
	range_new = new_max - new_min;
	f_x = ((range_new) * (x - old_min) / range_old) + new_min;
	return (f_x);
}

t_complex	create_complex(double x, double y)
{
	t_complex	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

static inline int	ft_atof_space_sign(int *i, char *s, int *sign)
{
	*sign = 1;
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
	while (s[*i] == '-' || s[*i] == '+')
	{
		if (s[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
	return (*sign);
}

double	ft_atof(char *s)
{
	int		i;
	double	tmp;
	double	n;
	int		sign;

	i = 0;
	tmp = 1;
	n = 0;
	sign = ft_atof_space_sign(&i, s, &sign);
	if (s[i] < '0' || s[i] > '9')
		return ((double) wrong_params_float());
	while (s[i] >= '0' && s[i] <= '9')
		n = n * 10 + (double)(s[i++] - 48);
	if (s[i++] == '.')
	{
		while (s[i] >= '0' && s[i] <= '9')
		{
			tmp = tmp * 10;
			n = n + (double)(s[i++] - 48) / tmp;
		}
	}
	else if (s[i] == ',')
		wrong_params_float();
	return (n * (double)sign);
}
