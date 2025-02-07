/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:32:46 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/07 23:30:27 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void my_mlx_pixel_put(t_data *data, unsigned int x, unsigned int y, unsigned int color)
{
    *(unsigned int*)(data->addr + (y * data->line_length + x * (data->bits_per_pixel >> 3))) = color;
}

static unsigned int find_color(const double x0, const double y0)
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

static t_cache set_point_in_cache(t_vars *ctx, t_cache cache, t_thread_data *data)
{
    const t_dvector offset = {
        .x = (ctx->zoom_x > 0) ? ctx->zoom_x * MANDELBROT_XMIN : -(ctx->zoom_x * MANDELBROT_XMAX),
        .y = 1.5 * ctx->zoom_y
    };
    t_vector p;
    
    // p.x = 0;
    // while (p.x < SCREEN_WIDTH)
    // {
    //     cache.cached_x[p.x] = MANDELBROT_XMIN + (ctx->center_x + p.x * ctx->zoom) * MANDELBROT_DX + (ctx->zoom - 1) * 0.5 - offset.x;
    //     p.x++;
    // }
    p.x = 0;
    while (p.x < SCREEN_WIDTH)
    {
        cache.cached_x[p.x] = MANDELBROT_XMIN + (ctx->center_x + p.x * ctx->zoom) * MANDELBROT_DX + (ctx->zoom - 1) * 0.5 - offset.x;
        p.x++;
    }
    p.y = data->start_row;
    while (p.y < data->end_row)
    {
        cache.cached_y[p.y] = MANDELBROT_YMIN + (ctx->center_y + p.y * ctx->zoom) * MANDELBROT_DY + offset.y;
        p.y++;
    }
    return (cache);
}


static int optimise_render(const t_vector p, const t_dvector y0, t_cache cache, t_vars *ctx)
{   
    const double x0 = cache.cached_x[p.x];
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


void* mandelbrot_thread(void* arg)
{
    t_thread_data   *data = (t_thread_data*)arg;
    t_vars* ctx = data->ctx;
    t_vector p;
    t_dvector y0;
    t_cache cache;
    
    p.x = 0;
    cache = set_point_in_cache(ctx, cache, data);
    p.y = data->start_row;
    while (p.y < data->end_row)
    {
        p.x = 0;
        y0.x = cache.cached_y[p.y];
        y0.y = y0.x * y0.x;
        while (p.x < SCREEN_WIDTH)
        {
            if (optimise_render(p, y0, cache, ctx))
            {
                p.x++;
                continue;
            }
            p.x++;
        }
        p.y++;
    }
    return NULL;
}

int mandelbrot(t_vars *ctx)
{
    pthread_t       threads[NUM_THREADS];
    t_thread_data   thread_args[NUM_THREADS];
    int rows_per_thread = SCREEN_HEIGHT / NUM_THREADS;
    
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].ctx = ctx;
        thread_args[i].start_row = i * rows_per_thread;
        thread_args[i].end_row = (i == NUM_THREADS - 1) ? SCREEN_HEIGHT : (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, mandelbrot_thread, &thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
