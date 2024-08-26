/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fracals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:49:30 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/26 16:29:17 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"


void	put_pixel(int x, int y, t_image *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bits_per_pixel) / 8);
	*((unsigned int *)(img->addr + offset)) = color;
}

void	fractol_render(t_calculate_fract_func calculate_fract, t_fract *fract)
{
	int	x;
	int	y;
	int	img_offset;
	int	step;

	step = 4;
	img_offset = 0;
	while (img_offset < step)
	{
		y = 0;
		while (y < HEIGHT)
		{
			x = img_offset;
			while (x < WIDTH)
			{
				calculate_fract(x, y, fract);
				x += step;
			}
			y += 1;
		}
		ft_printf("img offeset %i --> DONE \n", img_offset);
		mlx_put_image_to_window(fract->mlx_connexion, fract->mlx_window,
			fract->image.img, 0, 0);
		img_offset++;
	}
}

void	fractol_render_root(t_fract *fract)
{
	t_calculate_fract_func	calculate_fract;

	calculate_fract = NULL;
	if (fract->set == 1)
		calculate_fract = calculate_mandelbrot;
	else if (fract->set == 2)
		calculate_fract = calculate_julia;
	else if (fract->set == 3)
		calculate_fract = calculate_burning_ship;
	else if (fract->set == 4)
		calculate_fract = calculate_mandelbar;
	else if (fract->set == 5)
		calculate_fract = calculate_newton;
	fractol_render(calculate_fract, fract);
}
