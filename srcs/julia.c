/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:23:33 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/07 17:46:07 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include "fractol.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int julia(t_vars *ctx)
{
    double rate_x = JULIA_XMAX - JULIA_XMIN;
    double rate_y = JULIA_YMAX - JULIA_YMIN;
    double offset_x = (ctx->zoom_x > 0) ? ctx->zoom_x * JULIA_XMIN : -(ctx->zoom_x * JULIA_XMAX);
    double dx = rate_x / SCREEN_WIDTH;
    double dy = rate_y / SCREEN_HEIGHT;

    int px, py;
    double x0, y0;
    double complex c, z;
    int iter;
    
    c = ctx->params[0] + ctx->params[1] * I;
	
    double cached_x[SCREEN_WIDTH];
    for (px = 0; px < SCREEN_WIDTH; px++) {
        cached_x[px] = (JULIA_XMIN + (ctx->center_x / SCREEN_WIDTH) * rate_x + px * dx) * ctx->zoom + (ctx->zoom - 1) * 0.5 - offset_x;
    }

    for (py = 0; py < SCREEN_HEIGHT; py++) {
        y0 = (JULIA_YMIN + (ctx->center_y / SCREEN_HEIGHT) * rate_y + py * dy) * ctx->zoom + 1.5 * ctx->zoom_y;

        for (px = 0; px < SCREEN_WIDTH; px++) {
            x0 = cached_x[px];

            z = x0 + y0 * I;
            iter = 0;

            while (cabs(z) <= 2.0 && iter < MAX_ITER) {
                z = z * z + c;
                iter++;
            }
			
            int color = (iter == MAX_ITER) ? 0 : (iter * 16581375 / MAX_ITER);
            my_mlx_pixel_put(&ctx->img, px, py, color);
        }
    }
    return 0;
}

