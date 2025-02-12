/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:23:33 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/12 18:58:37 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include "fractol.h"

static inline void my_mlx_pixel_put(t_data *data, unsigned int x, unsigned int y, unsigned int color)
{
    *(unsigned int*)(data->addr + (y * data->line_length + x * 4)) = color;
}

// static t_cache set_point_in_cache_nothread(t_vars *ctx)
// {
//     t_cache cache;
//     const t_dvector offset = {
//         .x = 1.5 * ctx->zoom_x + 1.5 + JULIA_XMIN,
//         .y = 1.5 * ctx->zoom_y + 1.5 + JULIA_YMIN
//     };
//     unsigned int    i;
//     static const int half_screen_width = SCREEN_WIDTH / 2;
//     static const int half_screen_height = SCREEN_HEIGHT / 2;

//     double rate_x = JULIA_XMAX - JULIA_XMIN;
//     double rate_y = JULIA_YMAX - JULIA_YMIN;
//     double offset_x = (ctx->zoom_x > 0) ? ctx->zoom_x * JULIA_XMIN : -(ctx->zoom_x * JULIA_XMAX);
//     double dx = rate_x / SCREEN_WIDTH;
//     double dy = rate_y / SCREEN_HEIGHT;
    
//     i = 0;
//     while (i < SCREEN_WIDTH)
//     {
//         cache.cached_x[i] = (JULIA_XMIN + (ctx->center_x / SCREEN_WIDTH) * rate_x + p.x * dx) * ctx->zoom + (ctx->zoom - 1) * 0.5 - offset_x;
//         i++;
//     }
//     i = 0;
//     while (i < SCREEN_HEIGHT)
//     {
//         y0 = (JULIA_YMIN + (ctx->center_y / SCREEN_HEIGHT) * rate_y + p.y * dy) * ctx->zoom + 1.5 * ctx->zoom_y;
//         i++;
//     }
//     return (cache);
// }

static inline unsigned int find_color(const double x0, const double y0, double complex c)
{
    double complex z;
    unsigned int i;

    z = x0 + y0 * I;
    i = 0;

    while (cabs(z) <= 2.0 && i < MAX_ITER) {
        z = z * z + c;
        i++;
    }
    return (i - MAX_ITER) * COLOR_RANGE;
}

void    julia(t_vars *ctx)
{
    t_vector p;
    t_cache cache;
    double rate_x = JULIA_XMAX - JULIA_XMIN;
    double rate_y = JULIA_YMAX - JULIA_YMIN;
    double offset_x = (ctx->zoom_x > 0) ? ctx->zoom_x * JULIA_XMIN : -(ctx->zoom_x * JULIA_XMAX);
    double dx = rate_x / SCREEN_WIDTH;
    double dy = rate_y / SCREEN_HEIGHT;
    double x0, y0;
    double complex c;

    // cache = set_point_in_cache_nothread(ctx);
    c = ctx->params[0] + ctx->params[1] * I;
    while (p.x < SCREEN_WIDTH)
    {
        cache.cached_x[p.x] = (JULIA_XMIN + (ctx->center_x / SCREEN_WIDTH) * rate_x + p.x * dx) * ctx->zoom + (ctx->zoom - 1) * 0.5 - offset_x;
        p.x++;
    }
    p.y = 0;
    while (p.y < SCREEN_HEIGHT)
    {
        y0 = (JULIA_YMIN + (ctx->center_y / SCREEN_HEIGHT) * rate_y + p.y * dy) * ctx->zoom + 1.5 * ctx->zoom_y;
        p.x = 0;
        while (p.x < SCREEN_WIDTH)
        {
            my_mlx_pixel_put(&ctx->img, p.x, p.y, find_color(cache.cached_x[p.x], y0, c));
            p.x++;
        }
        p.y++;
    }
}

// void    julia2(t_vars *ctx)
// {
//     double rate_x = JULIA_XMAX - JULIA_XMIN;
//     double rate_y = JULIA_YMAX - JULIA_YMIN;
//     double offset_x = (ctx->zoom_x > 0) ? ctx->zoom_x * JULIA_XMIN : -(ctx->zoom_x * JULIA_XMAX);
//     double dx = rate_x / SCREEN_WIDTH;
//     double dy = rate_y / SCREEN_HEIGHT;

//     int px, py;
//     double x0, y0;
//     double complex c, z;
//     int iter;
    
//     c = ctx->params[0] + ctx->params[1] * I;
	
//     double cached_x[SCREEN_WIDTH];
//     for (px = 0; px < SCREEN_WIDTH; px++) {
//         cached_x[px] = (JULIA_XMIN + (ctx->center_x / SCREEN_WIDTH) * rate_x + px * dx) * ctx->zoom + (ctx->zoom - 1) * 0.5 - offset_x;
//     }

//     for (py = 0; py < SCREEN_HEIGHT; py++) {
//         y0 = (JULIA_YMIN + (ctx->center_y / SCREEN_HEIGHT) * rate_y + py * dy) * ctx->zoom + 1.5 * ctx->zoom_y;

//         for (px = 0; px < SCREEN_WIDTH; px++) {
//             x0 = cached_x[px];

//             z = x0 + y0 * I;
//             iter = 0;

//             while (cabs(z) <= 2.0 && iter < MAX_ITER) {
//                 z = z * z + c;
//                 iter++;
//             }
			
//             int color = (iter == MAX_ITER) ? 0 : (iter * 16581375 / MAX_ITER);
//             my_mlx_pixel_put(&ctx->img, px, py, color);
//         }
//     }
//     return 0;
// }

