/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:32:46 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/08 03:34:06 by abonneau         ###   ########.fr       */
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

static t_cache set_point_in_cache(t_vars *ctx, t_cache cache, t_thread_data *data)
{
    const t_dvector offset = {
        // .x = (ctx->zoom_x > 0) ? ctx->zoom_x * MANDELBROT_XMIN : -(ctx->zoom_x * MANDELBROT_XMAX),
        .x = 1.5 * ctx->zoom_x,
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
        cache.cached_x[p.x] = MANDELBROT_XMIN + (ctx->center_x + (double)((int)p.x - (SCREEN_WIDTH / 2)) * ctx->zoom) * (double)MANDELBROT_DX + offset.x + 1.5;
        p.x++;
    }
    p.y = data->start_row;
    while (p.y < data->end_row)
    {

        // p.y = 0;
        // -1.5 + (0 + (0 - 240) * 0.005) * 0.003 + 1.5 =
        cache.cached_y[p.y] = MANDELBROT_YMIN + (ctx->center_y + (double)((int)p.y - (SCREEN_HEIGHT / 2)) * ctx->zoom) * (double)MANDELBROT_DY + offset.y + 1.5;
        
        
        // cache.cached_y[p.y] =  ((int)p.y - 400) * 0.00375;
        // printf("p.y: %i, cache.cached_y[p.y]: %f\n", p.y, cache.cached_y[p.y]);
        p.y++;
    }
    // p.x = 0;
    // p.y = 0;
    // while (p.x < SCREEN_WIDTH)
    // {
    //     while (p.y < SCREEN_HEIGHT)
    //     {
    //         printf("p.x: %f, p.y: %f\n", cache.cached_x[p.x], cache.cached_y[p.y]);
    //         p.y++;
    //     }
    //     p.x++;
    // }
    return (cache);
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


// void* mandelbrot_thread(void* arg)
// {
//     t_thread_data   *data = (t_thread_data*)arg;
//     t_vars* ctx = data->ctx;
//     t_vector p;
//     t_dvector y0;
//     t_cache cache;
    
//     p.x = 0;
//     cache = set_point_in_cache(ctx, cache, data);
//     p.y = data->start_row;
//     while (p.y < data->end_row)
//     {
//         p.x = 0;
//         y0.x = cache.cached_y[p.y];
//         y0.y = y0.x * y0.x;
//         while (p.x < SCREEN_WIDTH)
//         {
//             if (optimise_render(p, y0, cache, ctx))
//             {
//                 p.x++;
//                 continue;
//             }
//             p.x++;
//         }
//         p.y++;
//     }
//     return NULL;
// }

// int mandelbrot_old(t_vars *ctx)
// {
//     pthread_t       threads[NUM_THREADS];
//     t_thread_data   thread_args[NUM_THREADS];
//     int rows_per_thread = SCREEN_HEIGHT / NUM_THREADS;
    
//     for (int i = 0; i < NUM_THREADS; i++) {
//         thread_args[i].ctx = ctx;
//         thread_args[i].start_row = i * rows_per_thread;
//         thread_args[i].end_row = (i == NUM_THREADS - 1) ? SCREEN_HEIGHT : (i + 1) * rows_per_thread;
//         pthread_create(&threads[i], NULL, mandelbrot_thread, &thread_args[i]);
//     }

//     for (int i = 0; i < NUM_THREADS; i++) {
//         pthread_join(threads[i], NULL);
//     }
//     return 0;
// }

t_cache set_point_in_cache_nothread(t_vars *ctx)
{
    t_cache cache;
    const t_dvector offset = {
        .x = 1.5 * ctx->zoom_x,
        .y = 1.5 * ctx->zoom_y
    };
    t_vector p;
    static const half_screen_width = SCREEN_HEIGHT / 2;
    
    p.x = 0;
    while (p.x < SCREEN_WIDTH)
    {
        cache.cached_x[p.x] = MANDELBROT_XMIN + (ctx->center_x + (double)((int)p.x - half_screen_width) * ctx->zoom) * (double)MANDELBROT_DX + offset.x + 1.5;
        p.x++;
    }
    p.y = 0;
    while (p.y < SCREEN_HEIGHT)
    {
        cache.cached_y[p.y] = MANDELBROT_YMIN + (ctx->center_y + (double)((int)p.y - half_screen_width) * ctx->zoom) * (double)MANDELBROT_DY + offset.y + 1.5;
        p.y++;
    }
    return (cache);
}

    
void* mandelbrot_nothread(t_vars *ctx)
{

    t_vector p;
    t_dvector y0;
    
    
    p.x = 0;
    t_cache cache;
    const t_dvector offset = {
        .x = 1.5 * ctx->zoom_x,
        .y = 1.5 * ctx->zoom_y
    };
    
    p.x = 0;
    while (p.x < SCREEN_WIDTH)
    {
        cache.cached_x[p.x] = MANDELBROT_XMIN + (ctx->center_x + (double)((int)p.x - (SCREEN_WIDTH / 2)) * ctx->zoom) * (double)MANDELBROT_DX + offset.x + 1.5;
        p.x++;
    }
    p.y = 0;
    while (p.y < SCREEN_HEIGHT)
    {
        cache.cached_y[p.y] = MANDELBROT_YMIN + (ctx->center_y + (double)((int)p.y - (SCREEN_HEIGHT / 2)) * ctx->zoom) * (double)MANDELBROT_DY + offset.y + 1.5;
        p.y++;
    }
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
    return NULL;
}

int mandelbrot(t_vars *ctx)
{
    // draw_axis(ctx);

    // int x = 0;
    // int y = 0;

    // // Calcul du centre des axes en tenant compte du zoom et du décalage
    // int axis_x = SCREEN_WIDTH / 2 - ctx->center_x;
    // int axis_y = SCREEN_HEIGHT / 2 - ctx->center_y;

    // // Dessin de l'axe horizontal (Y = 0)
    // if (axis_y >= 0 && axis_y < SCREEN_HEIGHT) // Vérifie qu'il est dans l'écran
    // {
    //     while (x < SCREEN_WIDTH)
    //     {
    //         my_mlx_pixel_put(&ctx->img, x, axis_y, 0xFFFFFF);
    //         x++;
    //     }
    // }

    // // Dessin de l'axe vertical (X = 0)
    // if (axis_x >= 0 && axis_x < SCREEN_WIDTH) // Vérifie qu'il est dans l'écran
    // {
    //     while (y < SCREEN_HEIGHT)
    //     {
    //         my_mlx_pixel_put(&ctx->img, axis_x, y, 0xFFFFFF);
    //         y++;
    //     }
    // }
    mandelbrot_nothread(ctx);
}
