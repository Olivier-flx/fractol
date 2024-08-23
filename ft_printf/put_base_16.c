/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_base_16.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:09:14 by ofilloux          #+#    #+#             */
/*   Updated: 2024/02/25 15:40:21 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	put_base16(unsigned int num, char *base, int control)
{
	int	count;

	count = 0;
	if (num > 15)
	{
		control = put_base16(num / 16, base, control);
		if (control == -1)
			return (-1);
		count += control;
		control = put_base16(num % 16, base, control);
		if (control == -1)
			return (-1);
		count += control;
	}
	else
	{
		if (write(1, &base[num], 1) == -1)
			return (-1);
		count ++;
	}
	return (count);
}
