/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 07:47:17 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/05 18:08:04 by abonneau         ###   ########.fr       */
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
# include <stdint.h>
# include <pthread.h>

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 800
# define MAX_ITER 1000
# define COLOR_RANGE (16581375 / MAX_ITER)

# define KEY_ESC 65307

# define MANDELBROT_XMIN -2.0
# define MANDELBROT_XMAX 1.0

# define MANDELBROT_YMIN -1.5
# define MANDELBROT_YMAX 1.5

# define MANDELBROT_DX ((MANDELBROT_XMAX - MANDELBROT_XMIN) / SCREEN_WIDTH)
# define MANDELBROT_DY ((MANDELBROT_YMAX - MANDELBROT_YMIN) / SCREEN_HEIGHT)

#define JULIA_XMIN -1.5
#define JULIA_XMAX 1.5
#define JULIA_YMIN -1.5
#define JULIA_YMAX 1.5

#define NUM_THREADS 4

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
    float           center_x;
    float           center_y;
    float           zoom_x;
    float           zoom_y;
    t_fractal_fn    fractal_fn;  // Pointeur vers une fonction de type t_fractal_fn
    double			params[2];   // Paramètres pour Julia ou Mandelbrot
    t_data          img;         // Structure pour l'image
} t_vars;

typedef struct e_thread_data {
    t_vars *ctx;
    int start_row;
    int end_row;
} t_thread_data;

typedef struct s_cache {
    float cached_x[SCREEN_WIDTH];
    float cached_y[SCREEN_HEIGHT];
} t_cache;


typedef struct s_dvector{
    double x;
    double y;
}   t_dvector;

typedef struct s_fvector{
    float x;
    float y;
}   t_fvector;

typedef struct s_vector{
    unsigned int x;
    unsigned int y;
}   t_vector;


int	mandelbrot(t_vars *ctx);
int	julia(t_vars *ctx);

double	ft_atof(const char *nptr);
size_t	ft_strlen(const char *s);
int		is_number(char *str);
int		ft_strcmp(const char *s1, const char *s2);
// void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif