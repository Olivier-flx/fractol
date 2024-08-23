/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:26:23 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/15 13:26:18 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	malloc_error(void)
{
	ft_printf("Erreur : %s\n", strerror(errno));
	errno = 0;
//	exit(EXIT_FAILURE);
}
