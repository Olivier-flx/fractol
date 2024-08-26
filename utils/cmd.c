/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:42:18 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/26 23:18:18 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

// in fractol.h
// inline void	decrease_definition(t_fract *data)
// inline void	improve_definition(t_fract *data)
// inline void	reset_coordinates(t_fract *data)

int	close_win(t_fract *fract)
{
	if ((fract->image.img) != NULL)
		mlx_destroy_image(fract->mlx_connexion, fract->image.img);
	if ((fract->mlx_window) != NULL)
		mlx_destroy_window(fract->mlx_connexion, fract->mlx_window);
	if ((fract->mlx_connexion) != NULL)
	{
		mlx_loop_end(fract->mlx_connexion);
		mlx_destroy_display(fract->mlx_connexion);
		free(fract->mlx_connexion);
	}
	exit(EXIT_SUCCESS);
}

int	handle_keybord_in(int keysym, t_fract *data)
{
	int	flag;

	flag = 0;
	if (keysym == XK_Escape)
		close_win(data);
	if (keysym == XK_Up || keysym == XK_Down \
		|| keysym == XK_Right || keysym == XK_Left)
		flag = offset_coordinates(keysym, data);
	if (keysym == XK_BackSpace)
		flag = reset_coordinates(data);
	if (keysym == XK_plus || keysym == XK_KP_Add)
		flag = improve_definition(data);
	if (keysym == XK_minus || keysym == XK_KP_Subtract)
		flag = decrease_definition(data);
	if (flag == 1)
		fractol_render_root(data);
	return (0);
}

static int	handle_clic_release(int keysym, int x, int y, t_fract *data)
{
	if (keysym == Button1 || keysym == Button3)
		data->is_dragging = 0;
	return (x * y);
}
//return (x*y); because if not x and y not used in the function --> cc error

int	handle_clic(int keysym, int x, int y, t_fract *data)
{
	if (keysym == Button1 || keysym == Button3)
	{
		if ((keysym == Button1 || keysym == Button3) && data->set != 2)
			if (data->is_dragging == 0)
				data->is_dragging = 1;
		if (keysym == Button1 && data->set == 2)
		{
			if (data->is_dragging == 0)
				data->is_dragging = -1;
		}
		if (keysym == Button3 && data->set == 2)
		{
			if (data->is_dragging == 0)
				data->is_dragging = 1;
		}
		data->mouse_x = x;
		data->mouse_y = y;
	}
	if (keysym == Button4)
		up_scale(data, x, y);
	if (keysym == Button5)
		down_scale(data, x, y);
	return (0);
}

void	cmd_mangement(t_fract *fract)
{
	mlx_hook(fract->mlx_window, KeyPress, KeyPressMask, \
		handle_keybord_in, fract);
	mlx_hook(fract->mlx_window, ButtonPress, ButtonPressMask, \
		handle_clic, fract);
	mlx_hook(fract->mlx_window, ButtonRelease, ButtonReleaseMask, \
		handle_clic_release, fract);
	mlx_hook(fract->mlx_window, MotionNotify, PointerMotionMask, \
		offset_mouse, fract);
	mlx_hook(fract->mlx_window, DestroyNotify, StructureNotifyMask, \
		close_win, fract);
}
