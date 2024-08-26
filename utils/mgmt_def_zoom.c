/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgmt_def_zoom.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:18:09 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/26 23:16:17 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

// in fractol.h
// inline void	decrease_definition(t_fract *data)
// inline void	improve_definition(t_fract *data)
// inline void	reset_coordinates(t_fract *data)


void	up_scale(t_fract *data, int x, int y)
{
	double	wx;
	double	wy;
	double	wx_after_z;
	double	wy_after_z;

	wx = (lin_interpol (x, -2, 2, WIDTH) / data->scale) - data->shift_x;
	wy = (lin_interpol (y, 2, -2, WIDTH) / data->scale) - data->shift_y;
	data->scale /= ZOOM_FACTOR;
	wx_after_z = (lin_interpol (x, -2, 2, WIDTH) / data->scale) - data->shift_x;
	wy_after_z = (lin_interpol (y, 2, -2, HEIGHT) / data->scale) \
		- data->shift_y;
	data->shift_x += (wx_after_z - wx);
	data->shift_y += (wy_after_z - wy);
	fractol_render_root(data);
}

void	down_scale(t_fract *data, int x, int y)
{
	double	wx;
	double	wy;
	double	wx_after_z;
	double	wy_after_z;

	wx = (lin_interpol (x, -2, 2, WIDTH) / data->scale) - data->shift_x;
	wy = (lin_interpol (y, 2, -2, WIDTH) / data->scale) - data->shift_y;
	data->scale *= ZOOM_FACTOR;
	wx_after_z = (lin_interpol (x, -2, 2, WIDTH) / data->scale) - data->shift_x;
	wy_after_z = (lin_interpol (y, 2, -2, HEIGHT) / data->scale) \
		- data->shift_y;
	data->shift_x += (wx_after_z - wx);
	data->shift_y += (wy_after_z - wy);
	fractol_render_root(data);
}

///////VERSION ZOOM verbeux et commented ////
//sx = screen x -> x position of the mouse relatively
// to the screeen and with ffractal coordonates (from -2 to 2)
// void up_scale(t_fract *data, int x, int y) {
// 	double	sx;
// 	double	sy;
// 	double	wx;
// 	double	wy;
// 	double	wx_after_z;
// 	double	wy_after_z;

// 	sx = lin_interpol (x, -2, 2, WIDTH);
// 	sy = lin_interpol (y, 2, -2, HEIGHT);

// 	wx = (sx / data->scale) - data->shift_x;
// 	wy = (sy / data->scale) - data->shift_y;

//     // Mise à jour de l'échelle (zoom)
// 	printf("data->scale before: %f \n",data->scale);
// 	data->scale /= ZOOM_FACTOR;
// 	printf("data->scale after: %f \n",data->scale);

// 	// calculer la position du point apres le zoom
// 	wx_after_z = (sx / data->scale) - data->shift_x;
// 	wy_after_z = (sy / data->scale) - data->shift_y;

// Recalcul des décalages pour que la souris reste centrée sur le même point

// 	printf("data->shift_x before: %f \t data->shift_y before:
// %f\n",data->shift_x, data->shift_y);
// 	data->shift_x += (wx_after_z - wx);/*- wy_after_z - wy;*/
// 	data->shift_y += (wy_after_z - wy);/*- wy_after_z - wy;*/
// 	printf("data->shift_x after: %f \t data->shift_y after:
//%f\n",data->shift_x, data->shift_y);
//     fractol_render_root(data);
// }


int	offset_coordinates(int keysym, t_fract *data)
{
	if (keysym == XK_Down)
		data->shift_y -= 0.1 * data->scale;
	if (keysym == XK_Up)
		data->shift_y += 0.1 * data->scale;
	if (keysym == XK_Left)
		data->shift_x -= 0.1 * data->scale;
	if (keysym == XK_Right)
		data->shift_x += 0.1 * data->scale;
	return (1);
}

void	moove_image(int x, int y, t_fract *data)
{
	double		delta_x;
	double		delta_y;
	static int	moove_counter = 0;

	if (data->is_dragging == 1)
	{
		delta_x = x - data->mouse_x;
		delta_y = y - data->mouse_y;
		data->shift_x -= delta_x * data->scale / WIDTH / 2;
		data->shift_y += delta_y * data->scale / WIDTH / 2;
		if (moove_counter >= 20)
		{
			fractol_render_root(data);
			data->mouse_x = x;
			data->mouse_y = y;
			moove_counter = 0;
		}
		moove_counter ++;
	}
}

int	offset_mouse(int x, int y, t_fract *data)
{
	if (data->is_dragging != 0)
	{
		if (data->is_dragging == 1)
			moove_image(x, y, data);
		if (data->is_dragging == -1)
		{
			data->c.x = lin_interpol (x, -2, 2, WIDTH);
			data->c.y = lin_interpol (y, -2, 2, HEIGHT);
			fractol_render_root(data);
		}
	}
	return (0);
}

/* /TEst v2
int	offset_mouse1(int x, int y, t_fract *data)
{
	t_complex	tmp;
	double		delta_x;
	double		delta_y;
	static int	moove_counter = 0;

	tmp = create_complex(0, 0);
	if (data->is_dragging == 1)
	{
		if (moove_counter == 0)
			tmp = create_complex(data->mouse_x, data->mouse_y);
		if (moove_counter >= 10)
		{
			// base:
			// delta_x = x - data->mouse_x;
			// delta_y = y - data->mouse_y;


			// delta_x = lin_interpol(x, -2,2,WIDTH) -
				//lin_interpol(tmp.x, -2,2,WIDTH);
			// delta_y = lin_interpol(y, 2,-2,WIDTH) -
				//lin_interpol(tmp.y, 2,-2,WIDTH);
			delta_x = ((double)x - tmp.x) * 4 / WIDTH;
			delta_y = ((double)y - tmp.y) * 4 / WIDTH;
			//delta_y = y - tmp.y;
			data->shift_x -= delta_x * data->scale;
			data->shift_y += delta_y * data->scale;
			fractol_render_root(data);
			moove_counter = 0;
		}
		moove_counter ++;
	}
	return (0);
}
*/
