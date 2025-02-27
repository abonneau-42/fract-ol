/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 07:47:17 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/19 11:27:47 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include "vector.h"

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 800
# define MAX_ITER 1000

# define MANDELBROT_XMIN -1.5
# define MANDELBROT_XMAX 1.5
# define MANDELBROT_YMIN -1.5
# define MANDELBROT_YMAX 1.5

# define JULIA_XMIN -1.5
# define JULIA_XMAX 1.5
# define JULIA_YMIN -1.5
# define JULIA_YMAX 1.5

typedef struct s_vars	t_vars;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_keyboard
{
	t_bool	arrow_left;
	t_bool	arrow_right;
	t_bool	arrow_top;
	t_bool	arrow_bottom;
	t_bool	escape;
	t_bool	scrollmouseup;
	t_bool	scrollmousedown;
}				t_keyboard;

typedef void			(*t_fractal_fn)(t_vars *ctx);

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	double			zoom;
	double			center_x;
	double			center_y;
	double			zoom_x;
	double			zoom_y;
	t_fractal_fn	fractal_fn;
	double			*params;
	t_data			img;
	t_keyboard		keyboard;
}	t_vars;

typedef struct s_cache
{
	double	cached_x[SCREEN_WIDTH];
	double	cached_y[SCREEN_HEIGHT];
}	t_cache;

void	mandelbrot(t_vars *ctx);
void	compute_const_val_x_mdb(t_vars *ctx, t_dvector *const_val_x);
void	compute_const_val_y_mdb(t_vars *ctx, t_dvector *const_val_y);

void	julia(t_vars *ctx);
void	compute_const_val_x_julia(t_vars *ctx, t_dvector *const_val_x);
void	compute_const_val_y_julia(t_vars *ctx, t_dvector *const_val_y);

int		close_window(t_vars *ctx);
void	redraw(t_vars *ctx);
int		key_hook(int keycode, t_vars *ctx);
int		mouse_hook(int mousecode, int x, int y, t_keyboard *keyboard);
void	parse_error_message(void);

double	ft_atof(const char *nptr);
size_t	ft_strlen(const char *s);
int		is_number(char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		is_float(char *chr, t_vars *ctx, int index);

#endif
