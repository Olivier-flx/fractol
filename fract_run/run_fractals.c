/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_fractals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:27:17 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/26 17:14:23 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	run_mandelbrot(t_fract *fract)
{
	fract->title = "Mandelbrot";
	initialize_var(fract);
	fract->set = 1;
	fractol_render_root(fract);
	cmd_mangement(fract);
	mlx_loop(fract->mlx_connexion);
}

void	run_julia(double r, double im, t_fract *fract)
{
	fract->title = "Julia";
	initialize_var(fract);
	fract->c.x = r;
	fract->c.y = im;
	fract->set = 2;
	fractol_render_root(fract);
	cmd_mangement(fract);
	mlx_loop(fract->mlx_connexion);
}

void	run_burning_ship(t_fract *fract)
{
	fract->title = "Burning Ship";
	initialize_var(fract);
	fract->set = 3;
	fractol_render_root(fract);
	cmd_mangement(fract);
	mlx_loop(fract->mlx_connexion);
}

void	run_mandelbar(t_fract *fract)
{
	fract->title = "Mandelbar";
	initialize_var(fract);
	fract->set = 4;
	fractol_render_root(fract);
	cmd_mangement(fract);
	mlx_loop(fract->mlx_connexion);
}

void	run_newton(t_fract *fract)
{
	fract->title = "Newton";
	initialize_var(fract);
	fract->set = 5;
	fract->iter_definition = 50;
	fractol_render_root(fract);
	cmd_mangement(fract);
	mlx_loop(fract->mlx_connexion);
}
