/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:33:59 by ofilloux          #+#    #+#             */
/*   Updated: 2024/02/25 15:49:41 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	print_ptr(unsigned long long ptr_value, char *base, int control)
{
	int	count;

	count = 0;
	if (ptr_value > 15)
	{
		control = print_ptr(ptr_value / 16, base, control);
		if (control == -1)
			return (-1);
		count += control;
		control = print_ptr(ptr_value % 16, base, control);
		if (control == -1)
			return (-1);
		count += control;
	}
	else
	{
		if (write(1, &base[ptr_value], 1) == -1)
			return (-1);
		count ++;
	}
	return (count);
}

int	put_ptr(void *ptr)
{
	int					count;
	int					control;
	unsigned long long	ptr_value;

	if (write(1, "0x", 2) == -1)
		return (-1);
	count = 2;
	control = 0;
	ptr_value = (unsigned long long) ptr;
	control = print_ptr(ptr_value, "0123456789abcdef", control);
	if (control == -1)
		return (-1);
	count += control;
	return (count);
}
