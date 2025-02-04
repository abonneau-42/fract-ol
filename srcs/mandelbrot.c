/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:32:46 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/04 18:08:38 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double fast_cabs(double complex z) {
    double x = fabs(creal(z));
    double y = fabs(cimag(z));
    return (x > y) ? (x + y * 0.5) : (y + x * 0.5);
}

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int mandelbrot(t_vars *ctx)
{
    double rate_x = MANDELBROT_XMAX - MANDELBROT_XMIN;
    double rate_y = MANDELBROT_YMAX - MANDELBROT_YMIN;
    double offset_x = (ctx->zoom_x > 0) ? ctx->zoom_x * MANDELBROT_XMIN : -(ctx->zoom_x * MANDELBROT_XMAX);
    double dx = rate_x / SCREEN_WIDTH;
    double dy = rate_y / SCREEN_HEIGHT;
    
    int px, py;
    double x0, y0;
    double complex c, z;
    int iter;
    
    double cached_x[SCREEN_WIDTH];
    for (px = 0; px < SCREEN_WIDTH; px++) {
        cached_x[px] = (MANDELBROT_XMIN + (ctx->center_x / SCREEN_WIDTH) * rate_x + px * dx) * ctx->zoom + (ctx->zoom - 1) * 0.5 - offset_x;
    }
    
    for (py = 0; py < SCREEN_HEIGHT; py++) {
        y0 = (MANDELBROT_YMIN + (ctx->center_y / SCREEN_HEIGHT) * rate_y + py * dy) * ctx->zoom + 1.5 * ctx->zoom_y;
        
        for (px = 0; px < SCREEN_WIDTH; px++) {
            x0 = cached_x[px];

            double q = (x0 - 0.25) * (x0 - 0.25) + y0 * y0;
            if (q * (q + (x0 - 0.25)) < 0.25 * y0 * y0) {
                my_mlx_pixel_put(&ctx->img, px, py, 0);
                continue;
            }
            if ((x0 + 1) * (x0 + 1) + y0 * y0 < 0.0625) {
                my_mlx_pixel_put(&ctx->img, px, py, 0);
                continue;
            }

            c = x0 + y0 * I;
            z = 0;
            iter = 0;
            
            double old_zx = 0.0, old_zy = 0.0;
            int period = 0;

            while (fast_cabs(z) <= 2.0 && iter < MAX_ITER) {
                z = z * z + c;
                iter++;
                
                if (iter % 20 == 0) {
                    if (fabs(creal(z) - old_zx) < 1e-6 && fabs(cimag(z) - old_zy) < 1e-6) {
                        iter = MAX_ITER;
                        break;
                    }
                    old_zx = creal(z);
                    old_zy = cimag(z);
                }
            }
            int color = (iter == MAX_ITER) ? 0 : (iter * 16581375 / MAX_ITER);
            my_mlx_pixel_put(&ctx->img, px, py, color);
        }
    }
    return 0;
}
