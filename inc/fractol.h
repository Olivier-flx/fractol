/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:05:09 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/23 15:22:58 by ofilloux         ###   ########.fr       */
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

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
//malloc
# include <unistd.h>
//write
# include <stdio.h>
//printf

# include <errno.h>
//errno
# include <string.h>

# include <X11/keysym.h>
# include <X11/X.h>
// keybord num for X11

//strerror
# include "./minilibx-linux/mlx.h"
# include "./ft_printf/ft_printf.h"
# include "colors.h"

	// fractol ID
	// MLX stuff
	//image
	// Hookes value
# ifndef WIDTH
#  define WIDTH 1000
# endif
# ifndef HEIGHT
#  define HEIGHT 1000
# endif


//square used to keep it simple

/*
If we initiate an image, we will have to pass a few pointers to which
	it will write a few important variables.
	The first one is the bpp, also called the bits per pixel.
	As the pixels are basically ints, these usually are 4 bytes,
	however, this can differ if we are dealing with a small endian (which
	means we most likely are on a remote display and only have 8 bit colors).
*/
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
	char	*title;
	void	*mlx_connexion; // mlx_init();
	void	*mlx_window; // mlx_new_window(void *mlx, int width, int height, char *title);
						//mlx_loop(mlx)
	t_image	image;

	//hooks member variable
	double	escape_val;//hypotenuse
	int		iter_definition;
	double	scale;
	double	shift_x;
	double	shift_y;
	double	mouse_x;
	double	mouse_y;
	int		is_dragging;

	// Julia init
	double	r;
	double	im;

	int		color;
	//tests
	int		colour;
}	t_fract;


void		malloc_error(void);
int			wrong_params_float();


int			ft_strncmp(char *input, char *comp_text, int n);
void		putstr_fd(char *str, int fd);
double		ft_atof(char *s);


/// Create_run.c
void		initialize_var(t_fract *fract);
void		run_julia (double r, double im, t_fract *fract);

/// fract_render.c
void		fractol_render(t_fract *fract);

//UTILS
/// MATH.c
double		linear_interpol(double x, double new_min, double new_max,
				double max);
double	rev_linear_interpol(double x, double new_min,
				double new_max, double max);
t_complex	square_z(t_complex z);
t_complex	sum_z(t_complex z1, t_complex z2);

//cmd.c
int			close_win(t_fract *fract);
int			handle_keybord_in(int keysym, t_fract *fract);
int			handle_clic(int keysym, int x, int y, t_fract *data);
void		cmd_mangement(t_fract *fract);

// mgmt_def_zoom.c
void		up_scale(t_fract *data, int x, int y);
void		down_scale(t_fract *data, int x, int y);
int			offset_coordinates(int keysym, t_fract *data);
int			offset_mouse(int x, int y, t_fract *data);

//KEY BORD INLINE FONCTION MANAGEMENT
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

#endif
