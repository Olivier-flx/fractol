/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_run_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:27:17 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/23 15:17:36 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	data_init_fractol(t_fract *fract)
{
	fract->escape_val = 4.0;
	fract->iter_definition = 30;
	fract->scale = 1.0;
	fract->shift_x = 0.0;
	fract->shift_y = 0.0;
	fract->color = 0;
	fract->mouse_x = 0.0;
	fract->mouse_y = 0.0;
	fract->is_dragging = 0;
	fract->r = 0.0;
	fract->im = 0.0;
}

void	run_julia (double r, double im, t_fract *fract)
{
	initialize_var(&fract);
	fract->title = "Julia";
	fract->r = r;
	fract->im = im;
	fractol_render(fract);
	cmd_mangement(fract);
	mlx_loop(fract->mlx_connexion);
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

	//events_loop init
	//event_listeners_loop(fract); ///TODO
	data_init_fractol(fract);
//	fractol_render(fract); --> USED IN MAIN
//	mlx_loop(fract->mlx_connexion); --> USED IN MAIN
}

