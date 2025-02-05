/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:32:46 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/05 18:14:37 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// static double fast_cabs(double complex z) {
//     double x = fabs(creal(z));
//     double y = fabs(cimag(z));
//     return (x > y) ? (x + y * 0.5) : (y + x * 0.5);
// }

// static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// int mandelbrot(t_vars *ctx)
// {
//     double rate_x = MANDELBROT_XMAX - MANDELBROT_XMIN;
//     double rate_y = MANDELBROT_YMAX - MANDELBROT_YMIN;
//     double offset_x = (ctx->zoom_x > 0) ? ctx->zoom_x * MANDELBROT_XMIN : -(ctx->zoom_x * MANDELBROT_XMAX);
//     double dx = rate_x / SCREEN_WIDTH;
//     double dy = rate_y / SCREEN_HEIGHT;
    
//     int px, py;
//     double x0, y0;
//     double complex c, z;
//     int iter;
//     double old_zx;
//     double old_zy;
//     int period;
    
//     double cached_x[SCREEN_WIDTH];
//     for (px = 0; px < SCREEN_WIDTH; px++) {
//         cached_x[px] = (MANDELBROT_XMIN + (ctx->center_x / SCREEN_WIDTH) * rate_x + px * dx) * ctx->zoom + (ctx->zoom - 1) * 0.5 - offset_x;
//     }
    
//     for (py = 0; py < SCREEN_HEIGHT; py++) {
//         y0 = (MANDELBROT_YMIN + (ctx->center_y / SCREEN_HEIGHT) * rate_y + py * dy) * ctx->zoom + 1.5 * ctx->zoom_y;
        
//         for (px = 0; px < SCREEN_WIDTH; px++) {
//             x0 = cached_x[px];

//             double q = (x0 - 0.25) * (x0 - 0.25) + y0 * y0;
//             if (q * (q + (x0 - 0.25)) < 0.25 * y0 * y0) {
//                 my_mlx_pixel_put(&ctx->img, px, py, 0);
//                 continue;
//             }
//             if ((x0 + 1) * (x0 + 1) + y0 * y0 < 0.0625) {
//                 my_mlx_pixel_put(&ctx->img, px, py, 0);
//                 continue;
//             }

//             c = x0 + y0 * I;
//             z = 0;
//             iter = 0;
//             old_zx = 0.0;
//             old_zy = 0.0;
//             period = 0;

//             while (fast_cabs(z) <= 2.0 && iter < MAX_ITER) {
//                 z = z * z + c;
//                 iter++;
                
//                 if (iter % 10 == 0) {
//                     if (fabs(creal(z) - old_zx) < 1e-6 && fabs(cimag(z) - old_zy) < 1e-6) {
//                         iter = MAX_ITER;
//                         break;
//                     }
//                     old_zx = creal(z);
//                     old_zy = cimag(z);
//                 }
//             }
//             int color = (iter == MAX_ITER) ? 0 : (iter * 16581375 / MAX_ITER);
//             my_mlx_pixel_put(&ctx->img, px, py, color);
//         }
//     }
//     return 0;
// }

static double fast_cabs(double complex z)
{
    const double x = fabs(creal(z));
    const double y = fabs(cimag(z));
    return (x > y) ? (x + y * 0.5) : (y + x * 0.5);
}

static void my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
    *(unsigned int*)(data->addr + (y * data->line_length + x * (data->bits_per_pixel >> 3))) = color;
}

static unsigned int find_color(const float x0, const float y0)
{
    int iter;
    double complex c;
    double complex z;
    t_dvector old_z;
    t_dvector old_z2;
    
    old_z = (t_dvector){.x = 0.0, .y=0.0};
    iter = 0;
    c = x0 + y0 * I;
    z = 0;
    while (fast_cabs(z) <= 2.0 && iter < MAX_ITER)
    {
        z = z * z + c;
        iter++;
        if (iter % 10 == 0)
        {
            old_z2 = (t_dvector){.x = creal(z), .y = cimag(z)}; 
            if (fabs(old_z2.x - old_z.x) < 1e-6 && fabs(old_z2.y - old_z.y) < 1e-6) {
                iter = MAX_ITER;
                break;
            }
            old_z.x = old_z2.x;
            old_z.y = old_z2.y;
        }
    }
    return ((MAX_ITER - iter) * COLOR_RANGE);
}

static t_cache set_point_in_cache(t_vars *ctx, t_cache cache)
{
    const t_fvector offset = {
        .x = (ctx->zoom_x > 0) ? ctx->zoom_x * MANDELBROT_XMIN : -(ctx->zoom_x * MANDELBROT_XMAX),
        .y = 1.5 * ctx->zoom_y
    };
    t_vector p;
    
    p.x = 0;
    while (p.x < SCREEN_WIDTH)
    {
        cache.cached_x[p.x] = MANDELBROT_XMIN + (ctx->center_x + p.x * ctx->zoom) * MANDELBROT_DX + (ctx->zoom - 1) * 0.5 - offset.x;
        p.x++;
    }
    p.y = 0;
    while (p.y < SCREEN_HEIGHT)
    {
        cache.cached_y[p.y] = MANDELBROT_YMIN + (ctx->center_y + p.y * ctx->zoom) * MANDELBROT_DY + offset.y;
        p.y++;
    }
    return (cache);
}


static int optimise_render(unsigned int px, unsigned int py, t_cache cache, t_vars *ctx)
{   
    const float x0 = cache.cached_x[px];
    const float y0 = cache.cached_y[py];
    const float y02 = y0 * y0;
    const float xv0 = (x0 - 0.25);
    const float q = xv0 * xv0 + y02;
    if (q * (q + xv0) < 0.25 * y02)
    {
        my_mlx_pixel_put(&ctx->img, px, py, 0);
        return (1);
    }
    if ((x0 + 1) * (x0 + 1) + y02 < 0.0625)
    {
        my_mlx_pixel_put(&ctx->img, px, py, 0);
        return (1);
    }
    my_mlx_pixel_put(&ctx->img, px, py, find_color(x0, y0));
    return (0);
}


void* mandelbrot_thread(void* arg)
{
    t_thread_data   *data = (t_thread_data*)arg;
    t_vars* ctx = data->ctx;
    unsigned int px;
    unsigned int py;
    t_cache cache;

    cache = set_point_in_cache(ctx, cache);
    py = data->start_row;
    while (py < data->end_row)
    {
        px = 0;
        while (px < SCREEN_WIDTH)
        {
            if (optimise_render(px, py, cache, ctx))
            {
                px++;
                continue;
            }
            px++;
        }
        py++;
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
