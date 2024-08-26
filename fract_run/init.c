/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:42:27 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/26 17:14:26 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	data_init_fractol(t_fract *fract)
{
	fract->set = 1;
	fract->escape_val = 4.0;
	fract->iter_definition = 30;
	fract->scale = 1;
	fract->shift_x = 0.0;
	fract->shift_y = 0.0;
	fract->color = 0;
	fract->mouse_x = 0.0;
	fract->mouse_y = 0.0;
	fract->is_dragging = 0;
	fract->c.x = 0.0;
	fract->c.y = 0.0;
}

void	initialize_var(t_fract *fract)
{
	fract->mlx_connexion = mlx_init();
	if (fract->mlx_connexion == NULL)
	{
		malloc_error();
		close_win(fract);
	}
	fract->mlx_window = mlx_new_window (fract->mlx_connexion, WIDTH, HEIGHT,
			fract->title);
	if (fract->mlx_window == NULL)
	{
		malloc_error();
		close_win(fract);
	}
	fract->image.img = mlx_new_image(fract->mlx_connexion, WIDTH, HEIGHT);
	if (fract->image.img == NULL)
	{
		malloc_error();
		close_win(fract);
	}
	fract->image.addr = mlx_get_data_addr(fract->image.img,
			&fract->image.bits_per_pixel,
			&fract->image.line_len, &fract->image.endian);
	data_init_fractol(fract);
}
