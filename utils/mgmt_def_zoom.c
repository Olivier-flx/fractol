/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgmt_def_zoom.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:18:09 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/23 21:45:24 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

// in fractol.h
// inline void	decrease_definition(t_fract *data)
// inline void	improve_definition(t_fract *data)
// inline void	reset_coordinates(t_fract *data)


//OFFSET PAS BON
/*
void	up_scale(t_fract *data, int x, int y)
{
	double	mouse_pos_x;
	double	mouse_pos_y;
//	double	old_zoom_level;
	double	mouse_pos_x_after;
	double	mouse_pos_y_after;
	mouse_pos_x = (x - data->shift_x) / data->scale;
    mouse_pos_y = (y - data->shift_y) / data->scale;
//	old_zoom_level = data->scale;
	data->scale *= 0.999;
	mouse_pos_x_after =  mouse_pos_x * 0.99;
	mouse_pos_y_after =  mouse_pos_y * 0.99;

	// data->shift_x += (mouse_pos_x - (x - data->shift_x) / data->scale) * data->scale;
	// data->shift_y += (mouse_pos_y - (y - data->shift_y) / data->scale) * data->scale;
	data->shift_x -= mouse_pos_x - mouse_pos_x_after;
	data->shift_y += mouse_pos_y - mouse_pos_y_after;
	// data->shift_y += (mouse_pos_y - mouse_pos_y_after);
	//data->shift_y = y - data->scale/ old_zoom_level * (y - data->shift_y );
	fractol_render_root(data);
}
*/

void	img_to_screen(float img_x, float img_y, float *screen_x, float *screen_y, t_fract *fract)
{
	*screen_x = img_x - fract->shift_x;
	*screen_y = img_y - fract->shift_y;
}

void	screen_to_img(float screen_x, float screen_y, float *img_x, float *img_y,  t_fract *fract)
{
	*img_x =  screen_x + fract->shift_x;
	*img_y = screen_y + fract->shift_y;
}

//sx = screen x -> x position of the mouse relatively to the screeen and with ffractal coordonates (from -2 to 2)
void up_scale(t_fract *data, int x, int y) {
    //double mouse_pos_x;
    //double mouse_pos_y;
    double zoom_factor = 0.9;
	double sx;
	double sy;
	double wx;
	double wy;
	double wx_after_z;
	double wy_after_z;

	printf("x = %i \t y = %i\n",x,y);

	sx = (double)x / WIDTH * 4; //  / data->scale + data->shift_x;
	sy = (double)y / HEIGHT * 4; //  / data->scale + data->shift_y;
	wx = (sx + data->shift_x) * data->scale;
	wy = (sy + data->shift_y) * data->scale;

	printf("sx avant : %f \t sy avant: %f\n", sx, sy);
	printf("wx avant : %f \t wy avant: %f\n", wx, wy);

    // Mise à jour de l'échelle (zoom)
	printf("data scale avant: %f \n", data->scale);
    data->scale *= zoom_factor;
	printf("data scale apres: %f\n", data->scale);

	// calculer la position du point apres le zoom
	wx_after_z = (wx / zoom_factor) / 2;
	wy_after_z = (wy / zoom_factor) / 2;
	printf("wx_after_z: %f \t wy_after_z: %f\n",wx_after_z, wy_after_z);
//	printf("sx_after_z: %f \t\t sy_after_z : %f\n",sx_after_z, sy_after_z);

	printf("data->shift_x before : %f \t data->shift_y before: %f\n",data->shift_x, data->shift_y);

    // Recalcul des décalages pour que la souris reste centrée sur le même point
	//data->shift_x = data->shift_x - ((2 - (2 - sx)) - ((wx - 2) * zoom_factor - (2 - wx))); /* - (wx_after_z - wx;*/
	//	data->shift_y = data->shift_y - ((2 - (2 - sy)) - ((wx - 2) * zoom_factor - (2 - wy))); /* - (wx_after_z - wx;*/

	data->shift_y -= data->shift_y - (wy_after_z - wy) / 2;/*- wy_after_z - wy;*/
	printf("data->shift_x after: %f \t data->shift_y after: %f\n",data->shift_x, data->shift_y);

	//data->shift_x = (sx - ( data->shift_x + 2 + sx - (4 / 2)) * (zoom_factor / 2));
	//data->shift_y = (sx - ( data->shift_y + 2 + sx - (4 / 2)) * (zoom_factor / 2));
    //data->shift_y = (sy - (4 / 2)) * (zoom_factor / 2);

    // Remettre les shift_x et shift_y sur une échelle de -2 à 2
//    data->shift_x = (data->shift_x / WIDTH) * (4.0 - 2.0);
//    data->shift_y = (data->shift_y / HEIGHT) * (4.0 - 2.0);
//	printf("data scale après: %f \t\t shift_x après : %f \t\t shift_y après: %f\n",data->scale, data->shift_x, data->shift_y);

    // Redessiner la fractale avec les nouvelles valeurs
    fractol_render_root(data);
}

void down_scale(t_fract *data, int x, int y) {
    double mouse_pos_x;
    double mouse_pos_y;
    double zoom_factor = 1.01;  // ou une autre valeur selon votre besoin

    // Calcul de la position de la souris en coordonnées fractales
    mouse_pos_x = (rev_lin_interpol(x, 0, WIDTH, 2) - WIDTH / 2) / data->scale - data->shift_x;
    mouse_pos_y = (rev_lin_interpol(y, 0, HEIGHT, 2) - HEIGHT / 2) / data->scale - data->shift_y;
	printf("data scale avant: %f \t mouse_pos_x avant : %f \t mouse_pos_y avant: %f\n",data->scale, mouse_pos_x, mouse_pos_y);
	printf("shift_x avant: %f \t shift_y avant : %f \n",data->shift_x, data->shift_y);

    // Mise à jour de l'échelle (zoom)
    data->scale *= zoom_factor;

    // Recalcul des décalages pour que la souris reste centrée sur le même point
    data->shift_x = mouse_pos_x - (x - WIDTH / 2) / data->scale;
    data->shift_y = mouse_pos_y - (y - HEIGHT / 2) / data->scale;

    // Remettre les shift_x et shift_y sur une échelle de -2 à 2
    data->shift_x = (data->shift_x / WIDTH) * 2.0;
    data->shift_y = (data->shift_y / HEIGHT) * 2.0;
	printf("data scale après: %f \t shift_x après : %f \t shift_y après: %f\n",data->scale, data->shift_x, data->shift_y);

    // Redessiner la fractale avec les nouvelles valeurs
    fractol_render_root(data);
}

/*
void	down_scale(t_fract *data, int x, int y)
{
	double	mouse_pos_x;
	double	mouse_pos_y;
	double	old_zoom;
	// double	mouse_pos_x_after;
	// double	mouse_pos_y_after;

	old_zoom = data->scale;
	mouse_pos_x = (x - WIDTH / 2) / data->scale + data->shift_x;
	mouse_pos_y = (y - HEIGHT / 2) / data->scale + data->shift_y;
	printf("data scale avant: %f \t\t mouse_pos_x avant : %f \t\t mouse_pos_y avant: %f\n",data->scale, mouse_pos_x, mouse_pos_y);
	data->scale *= 1.01;

	// mouse_pos_x_after = mouse_pos_x - (x - WIDTH / 2) / data->scale;
	// mouse_pos_y_after = mouse_pos_y - (y - HEIGHT / 2) / data->scale;
	printf("shift_x avant: %f \t\t shift_y avant : %f\n", data->shift_x, data->shift_x);
	data->shift_x = mouse_pos_x - data->scale / old_zoom * (mouse_pos_x - data->shift_x) ;
	data->shift_y = mouse_pos_x - data->scale / old_zoom * (mouse_pos_y - data->shift_y) ;
	printf("data scale après: %f \t\t shift_x après : %f \t\t shift_y après: %f\n",data->scale, data->shift_x, data->shift_y);

	// data->shift_x = mouse_pos_x_after;
	// data->shift_y = mouse_pos_y_after;
		//printf("data scale après: %f \t\t data->shift_x : %f \t\t data->shift_y: %f\n",data->scale, data->shift_x, data->shift_y);



	// printf("mx avant : %f \t\t mx après: %f\n", mouse_pos_x, mouse_pos_x_after);
	// printf("data->shift x before= %f \n", data->shift_x);
	// if (x > WIDTH / 2)
	// 	data->shift_x -= (WIDTH / 2 - (mouse_pos_x - mouse_pos_x_after)) * data->scale;
	// else
	// {
	// 	data->shift_x = x - mouse_pos_x * data->scale;
	// 	printf("data->shift x = %f \n", data->shift_x);
	// }
	// printf("data->shift y before = %f \n", data->shift_y);
	// if (y > HEIGHT / 2)
	// 	data->shift_y += (HEIGHT / 2 - (mouse_pos_y - mouse_pos_y_after)) * data->scale;
	// else
	// {
	// 	data->shift_y = y - mouse_pos_y * data->scale;
	// 	printf("data->shift y = %f \n", data->shift_y);
	// }
	fractol_render_root(data);
}
*/
/*
void	down_scale(t_fract *data, int x, int y)
{
	double	mouse_pos_x;
	double	mouse_pos_y;

	mouse_pos_x = (x - WIDTH / 2) * data->scale + data->shift_x;
	mouse_pos_y = (y - HEIGHT / 2) * data->scale + data->shift_y;
	data->scale *= 1.001;
	data->shift_x = mouse_pos_x - (x - WIDTH / 2) * data->scale;
	data->shift_y = mouse_pos_y - (y - HEIGHT / 2) * data->scale;
	fractol_render_root(data);
}
*/

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

int	offset_mouse(int x, int y, t_fract *data)
{
	double delta_x;
	double delta_y;
	static int moove_counter = 0;

	if (data->is_dragging == 1)
	{
		delta_x = x - data->mouse_x;
		delta_y = y - data->mouse_y;

		data->shift_y += delta_y * 0.00001 * data->scale;
		data->shift_x -= delta_x * 0.00001 * data->scale;
		moove_counter ++;
		if (moove_counter >= 20)
		{
			fractol_render_root(data);
			moove_counter = 0;
		}
	}
	return (0);
}
