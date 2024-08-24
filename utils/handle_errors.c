/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:26:23 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/23 16:32:01 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	malloc_error(void)
{
	ft_printf("Erreur : %s\n", strerror(errno));
	errno = 0;
//	exit(EXIT_FAILURE);
}

int	wrong_params_float(void)
{
	ft_printf("Erreur : the 2nd or the 3 parameter in not a valid number\n");
	return (exit(EXIT_FAILURE), 1);
}
