/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_numb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:33:16 by ofilloux          #+#    #+#             */
/*   Updated: 2024/02/25 13:33:27 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	write_integ(int n, int control)
{
	char	c;
	int		n_digits;

	if (control == -1)
		return (-1);
	n_digits = 1;
	if (n >= 10)
	{
		control = write_integ(n / 10, control);
		if (control == -1)
			return (-1);
		n_digits += control;
	}
	c = n % 10 + '0';
	if (write(1, &c, 1) == -1)
		return (-1);
	return (n_digits);
}

int	put_integer(int integ)
{
	int	count;
	int	control;

	count = 0;
	control = 0;
	if (integ == -2147483648)
	{
		if (write(1, "-2147483648", 11) == -1)
			return (-1);
		return (11);
	}
	if (integ < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		integ *= -1;
		count = 1;
	}
	control = write_integ (integ, control);
	if (control == -1)
		return (-1);
	count += control;
	return (count);
}

int	write_unsigned_int(unsigned int num, int control)
{
	char	c;
	int		n_digits;

	if (control == -1)
		return (control);
	n_digits = 1;
	if (num >= 10)
	{
		control = write_unsigned_int(num / 10, control);
		if (control == -1)
			return (-1);
		n_digits += control;
	}
	c = num % 10 + '0';
	if (write(1, &c, 1) == -1)
		return (-1);
	return (n_digits);
}

int	put_unsigned_int(unsigned int num)
{
	int	count;
	int	control;

	control = 0;
	count = write_unsigned_int(num, control);
	if (count == -1)
		return (-1);
	return (count);
}
