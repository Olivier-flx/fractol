/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:05:09 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/26 23:35:50 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//External functions autorized.
//    • open, close, read, write, malloc, free, perror, strerror, exit
//    • All functions of the math library (-lm compiler option,man man 3 math)
//    • All functions of the MiniLibX
//    • ft_printf and any equivalent YOU coded

//https://harm-smits.github.io/42docs/libs/
	//minilibx/getting_started.html#installation
//https://github.com/ilkou/minilibx

//////////////// In this file: ///////////////////
///// Libraries
///// Macros
///// typedefs
///////// UTILS
///////// FRACTAL & RENDER
///////// KEY BORD cmd & INLINE FONCTION MANAGEMENT
///////// ERROR messages

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
//malloc
# include <unistd.h>
//write
# include <stdio.h>
//printf

# include <math.h>

# include <errno.h>
//errno
# include <string.h>
//strerror

# include <X11/keysym.h>
# include <X11/X.h>
// keybord num for X11

# include "./minilibx-linux/mlx.h"
# include "./ft_printf/ft_printf.h"
# include "colors.h"

# ifndef WIDTH
#  define WIDTH 800
# endif
# ifndef HEIGHT
#  define HEIGHT 800
# endif

// precision for newton root approximation
# define TOLERANCE 0.0001
# define ZOOM_FACTOR 1.01

typedef struct s_image
{
	void	*img; // pointer to image struc
	char	*addr; //points to the acutal pixel (pixel pointer)
	int		bits_per_pixel; //bits per pixel
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_complex
{
	double	x;
	double	y;
}		t_complex;

typedef struct s_fractol
{
	char		*title;
	void		*mlx_connexion;
	void		*mlx_window;
	t_image		image;
	//other variable
	int			set;
	double		escape_val; //hypotenuse
	int			iter_definition;
	double		scale;
	double		shift_x;
	double		shift_y;
	//cmd
	double		mouse_x;
	double		mouse_y;
	int			is_dragging;
	// C values
	t_complex	c;
	int			color;
}	t_fract;

// To select the right type of rendering accordingly to the fractal selected
typedef void	(*t_calculate_fract_func)(int x, int y, t_fract *fract);

///////////// FRACTAL & RENDER //////////////
/// fract_run/init.c
void		initialize_var(t_fract *fract);
/// fract_run/run_fractals.c
void		run_mandelbrot(t_fract *fract);
void		run_julia(double r, double im, t_fract *fract);
void		run_burning_ship(t_fract *fract);
void		run_mandelbar(t_fract *fract);
void		run_newton(t_fract *fract);

/// fract_run/Calculate_fractols.c
void		calculate_mandelbrot(int x, int y, t_fract *fract);
void		calculate_julia(int x, int y, t_fract *fract);
void		calculate_burning_ship(int x, int y, t_fract *fract);
void		calculate_mandelbar(int x, int y, t_fract *fra);
void		calculate_newton(int x, int y, t_fract *fract);
/// fract_run/newton_utils.c
t_complex	f_z(t_complex z);
t_complex	f_prime_z(t_complex z);
t_complex	f_zn_plus_1(t_complex z_n, t_complex z, t_complex f_z_prime);
t_complex	newton_iteration(t_complex zn);
int			is_tolerance_ok(t_fract *fract, t_complex zn1);

/// fract_run/render_fractals.c
void		fractol_render_root(t_fract *fract);
void		put_pixel(int x, int y, t_image *img, int color);

///////////// UTILS //////////////
void		malloc_error(void);
int			wrong_params_float(void);

/// utils/validation.c
int			ft_strncmp(char *input, char *comp_text, int n);
void		putstr_fd(char *str, int fd);

/// utils/math.c
double		ft_atof(char *s);
t_complex	create_complex(double x, double y);
double		lin_interpol(double x, double start, double end,
				double screen_size);
double		rev_lin_interpol(double x, double new_min,
				double new_max, double max);

// Complex math.c
t_complex	sum_z(t_complex z1, t_complex z2);
t_complex	square_z(t_complex z);
t_complex	multiply_z(t_complex a, t_complex b);
t_complex	divide_z(t_complex a, t_complex b);
t_complex	substracte_z(t_complex z1, t_complex z2);

/// utils/handel_error.c

/////////  KEY BORD cmd & INLINE FONCTION MANAGEMENT ////////////
// cmd.c
int			close_win(t_fract *fract);
int			handle_keybord_in(int keysym, t_fract *fract);
int			handle_clic(int keysym, int x, int y, t_fract *data);
void		cmd_mangement(t_fract *fract);

// mgmt_def_zoom.c
void		up_scale(t_fract *data, int x, int y);
void		down_scale(t_fract *data, int x, int y);
int			offset_coordinates(int keysym, t_fract *data);
int			offset_mouse(int x, int y, t_fract *data);

static inline int	decrease_definition(t_fract *data)
{
	data->iter_definition -= 10;
	return (1);
}

static inline int	improve_definition(t_fract *data)
{
	data->iter_definition += 10;
	return (1);
}

static inline int	reset_coordinates(t_fract *data)
{
	data->shift_x = 0.0;
	data->shift_y = 0.0;
	data->scale = 1;
	return (1);
}

# define ERROR_MSG_JULIA "Don't forget put a dot \".\" instead \
	of a \",\" for float values arguments\n"
# define ERROR_MSG_JULIA_2 "Try ./fractol julia with some values like :\
	\n\t-0.8 0.156 \n\tor 0 0.8\n\tor 0.285 0.01\n"
# define ERROR_MSG "Try ./fractol with the following arguments : \
	\n\t--> mandelbrot\n\t--> julia <agr float1> <agr float1> avec floats betwween -2 and 2\
	\n\t--> burning\n\t--> mandelbar\n\t--> newton\n"
#endif
