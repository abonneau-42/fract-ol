/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 07:47:17 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/04 18:29:43 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <complex.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 800
# define MAX_ITER 100

# define KEY_ESC 65307

# define MANDELBROT_XMIN -2.0
# define MANDELBROT_XMAX 1.0

# define MANDELBROT_YMIN -1.5
# define MANDELBROT_YMAX 1.5

# define RATE_MB_X MANDELBROT_XMAX - MANDELBROT_XMIN
# define RATE_MB_Y MANDELBROT_YMAX - MANDELBROT_YMIN

#define JULIA_XMIN -1.5
#define JULIA_XMAX 1.5
#define JULIA_YMIN -1.5
#define JULIA_YMAX 1.5

typedef struct s_vars t_vars;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef int (*t_fractal_fn)(t_vars *ctx);  // Déclaration correcte pour le type de la fonction

typedef struct s_vars {
    void            *mlx;
    void            *win;
    float           zoom;
    double          center_x;
    double          center_y;
    double          zoom_x;
    double          zoom_y;
    t_fractal_fn    fractal_fn;  // Pointeur vers une fonction de type t_fractal_fn
    double			params[2];   // Paramètres pour Julia ou Mandelbrot
    t_data          img;         // Structure pour l'image
} t_vars;


int	mandelbrot(t_vars *ctx);
int	julia(t_vars *ctx);

double	ft_atof(const char *nptr);
size_t	ft_strlen(const char *s);
int		is_number(char *str);
int		ft_strcmp(const char *s1, const char *s2);
// void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif