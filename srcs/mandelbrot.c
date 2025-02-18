/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:32:46 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/18 11:21:12 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline void my_mlx_pixel_put(t_data *data, unsigned int x, unsigned int y, unsigned int color)
{
    *(unsigned int*)(data->addr + (y * data->line_length + x * 4)) = color;
}

static inline unsigned int find_color(const double x0, const double y0)
{
    t_dvector oldz;
    t_dvector z;
    double temp;
    int i;

    oldz = (t_dvector){.x = 0.0, .y=0.0};
    z = (t_dvector){.x = 0.0, .y=0.0};
    i = 0;
    while ((z.x * z.x + z.y * z.y) < 4.0 && i < MAX_ITER) {
        temp = z.x * z.x - z.y * z.y + x0;
        z.y = 2.0 * z.x * z.y + y0;
        z.x = temp;

        if (i % 20 == 0) {
            if ( (z.x - oldz.x) * (z.x - oldz.x) < 1e-12 && (z.y - oldz.y) *  (z.y - oldz.y) < 1e-12) {
                i = MAX_ITER;
                break;
            }
            oldz.x = z.x;
            oldz.y = z.y;
        }
        i++;
    }
    return (i - MAX_ITER) * COLOR_RANGE;
}

static inline int optimise_render(const t_vector p, const t_dvector y0, const double x0, t_vars *ctx)
{  
    const double xv0 = (x0 - 0.25);
    const double q = xv0 * xv0 + y0.y;
    if (q * (q + xv0) < 0.25 * y0.y || (x0 + 1) * (x0 + 1) + y0.y < 0.0625)
    {
        my_mlx_pixel_put(&ctx->img, p.x, p.y, 0);
        return (1);
    }
    my_mlx_pixel_put(&ctx->img, p.x, p.y, find_color(x0, y0.x));
    return (0);
}

static t_cache set_point_in_cache_nothread(t_vars *ctx)
{
    t_cache cache;
    const t_dvector offset = {
        .x = 1.5 * ctx->zoom_x + 1.5 + MANDELBROT_XMIN,
        .y = 1.5 * ctx->zoom_y + 1.5 + MANDELBROT_YMIN
    };
    unsigned int    i;
    static const int half_screen_width = SCREEN_WIDTH / 2;
    static const int half_screen_height = SCREEN_HEIGHT / 2;
    
    i = 0;
    while (i < SCREEN_WIDTH)
    {
        cache.cached_x[i] = (ctx->center_x + (double)((int)i - half_screen_width) * ctx->zoom) * (double)MANDELBROT_DX + offset.x;
        i++;
    }
    i = 0;
    while (i < SCREEN_HEIGHT)
    {
        cache.cached_y[i] = (ctx->center_y + (double)((int)i - half_screen_height) * ctx->zoom) * (double)MANDELBROT_DY + offset.y;
        i++;
    }
    return (cache);
}

void    mandelbrot(t_vars *ctx)
{
    t_vector p;
    t_dvector y0;
    t_cache cache;

    cache = set_point_in_cache_nothread(ctx);
    p.y = 0;
    while (p.y < SCREEN_HEIGHT)
    {
        p.x = 0;
        y0.x = cache.cached_y[p.y];
        y0.y = y0.x * y0.x;
   
        while (p.x < SCREEN_WIDTH)
        {
            if (optimise_render(p, y0, cache.cached_x[p.x], ctx))
            {
                p.x++;
                continue;
            }
            p.x++;
        }
        p.y++;
    }
}
