/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:55:38 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/19 18:13:48 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/fractol.h"

/* ////// rendering /////

    • Your program must offer the Julia set and the Mandelbrot set.
    • The mouse wheel zooms in and out, almost infinitely (within the limits of the computer). This is the very principle of fractals.
    • You must be able to create different Julia sets by passing different parameters to the program.
    • A parameter is passed on the command line to define what type of fractal will be displayed in a window.
        ◦ You can handle more parameters to use them as rendering options.
       ◦ If no parameter is provided, or if the parameter is invalid, the program displays a list of available parameters and exits properly.
    • You must use at least a few colors to show the depth of each fractal. It’s even better if you hack away on psychedelic effects.

   ////// Graphic management /////
    • Your program has to display the image in a window.
    • The management of your window must remain smooth (changing to another window, minimizing, and so forth).
    • Pressing ESC must close the window and quit the program in a clean way.
    • Clicking on the cross on the window’s frame must close the window and quit the program in a clean way.
    • The use of the images of the MiniLibX is mandatory.
*/

	int	main(int ac, char **av)
	{
		t_fract fract;

		if (ac == 2 && ft_strncmp(av[1], "mandelbrot", 10) == 0)
		{
			fract.title = av[1];
			initialize_var(&fract);
			fractol_render(&fract);
			cmd_mangement(&fract);
			mlx_loop(fract.mlx_connexion);
		}
		else if (ac == 4 && ft_strncmp(av[1], "julia", 5) == 0)
		{
			fract.title = "Julia";
			//run julia fractol
		}
		if ((ac == 2 || ac == 3) && ft_strncmp(av[1], "julia", 5) == 0)
		{
			//print accepted julia args
			putstr_fd("ERROR_MESSAGE", STDERR_FILENO);
		}
		else
		{
			putstr_fd("ERROR_MESSAGE", STDERR_FILENO); // to implement error message
			//print_params_option();
			//displays a list of available parameters
			//and exits properly.
		}
		mlx_loop_end(fract.mlx_connexion);
		return(0);
	}


//////TEST AND PRACTICE /////////
/*
void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	int	dst;

	dst = (y * data->line_len) + (x * (data->bits_per_pixel / 8));
	*((unsigned int *)(dst + data->addr)) = color;
}

int handle_input (int keysym, t_fract *data)
{
	if (keysym == XK_Escape)
	{
		printf("the %d key (ESC) has been pressed\n\n", keysym);
		mlx_destroy_window(data->mlx_connexion, data->mlx_window);
		mlx_destroy_display(data->mlx_connexion);
		free(data->mlx_connexion);
		exit (EXIT_FAILURE);
	}
	printf("The %d key has been pressed \n\n", keysym);
	return (0);
}

int     button_press(int button, int x, int y, t_fract *da)
{
    if (button == 1)
        printf("Left mouse button pressed at (%d, %d)!\n", x, y);
    else if (button == 3)
        printf("Right mouse button pressed at (%d, %d)!\n", x, y);

    return (0);
}

void	color_screen(t_fract *data, int color)
{
	for (int y = 0; y < 800; ++y)
	{
		for (int x = 0; x < 800; ++x)
		{
			my_mlx_pixel_put(&data->image,
						x,
						y,
						color);
		}
	}
}

int	color_text(t_fract *data)
{
	mlx_string_put(data->mlx_connexion, data->mlx_window, 150, 150, data->colour, "Color Changing Window!");
	return (0);
}

int	change_color(int keysym, t_fract *data)
{
	// Fill the window with the current color
//  mlx_clear_window(data->mlx, data->win);

	// Cycle through some basic colors: RED, GREEN, BLUE
	if (keysym == XK_r)		// If it's red
	{
		color_screen(data, 0xff0000);
		data->colour = 0x00FF00;		// Change to green
	}
	else if (keysym == XK_g)	// If it's green
	{
		color_screen(data, 0xff00);
		data->colour = 0x0000FF;		// Change to blue
	}
	else if (keysym == XK_b)
	{
		color_screen(data, 0xff);
		data->colour = 0xff0000;		// Change to blue
	}
	else if (keysym == XK_Escape)

		exit (1);
	mlx_put_image_to_window(data->mlx_connexion, data->mlx_window, data->image.img, 0, 0);
	// 0 et 0 are offsets
	mlx_loop_hook(data->mlx_connexion, color_text, data);
	return (0);
}


int main()
{
	t_fract fract;

	fract.mlx_connexion = mlx_init();
	if (!fract.mlx_connexion)
		exit(EXIT_FAILURE);
	fract.mlx_window = mlx_new_window(fract.mlx_connexion, 800, 800, "test");
	if (!fract.mlx_connexion)
	{
		mlx_destroy_display(fract.mlx_connexion);
		free (fract.mlx_connexion);
		exit(EXIT_FAILURE);
	}
	fract.image.img = mlx_new_image(fract.mlx_connexion, 800, 800);
	if (!fract.image.img)
	{
		mlx_destroy_window(fract.mlx_connexion, fract.mlx_window);
		mlx_destroy_display(fract.mlx_connexion);
		free(fract.mlx_connexion);
		exit(EXIT_FAILURE);
	}

	fract.image.addr = mlx_get_data_addr(fract.image.img,
												&fract.image.bits_per_pixel,
												&fract.image.line_len,
												&fract.image.endian);
//	mlx_key_hook(fract.mlx_window,
//				change_color,
//				&fract);

	mlx_key_hook(fract.mlx_window, handle_input, &fract);
//	mlx_hook(fract.mlx_window, ButtonPress,
//		ButtonPressMask, &button_press, &fract);
//	mlx_loop_hook(fract.mlx_connexion, change_color, &fract); //active while no event
	mlx_key_hook(fract.mlx_window, change_color, &fract);

//	fract.image.addr = mlx_get_data_addr(&fract.image.addr, &fract.image.bits_per_pixel,
//		&fract.image.line_len, &fract.image.endian);
//	my_mlx_pixel_put(fract.image.img, 200, 200, 0x00FF0000);
	mlx_loop(fract.mlx_connexion);
}
*/
