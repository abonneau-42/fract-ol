#include "fractol.h"

int main() {
    double cx, cy;
    double zx, zy;
    double xsqr, ysqr;
    int i, maxIterations = 1000;
    int x = 0;
    t_dvector oldz;


    clock_t start, end;
    double elapsed_time;
    start = clock(); // Début du chronomètre
    while (x < 640000)
    {
        cx = -0.786;
        cy = 0.268;
        zx = 0.0;
        zy = 0.0;
        xsqr = 0.0;
        ysqr = 0.0;
        oldz = (t_dvector){.x = 0.0, .y=0.0};
        i = 0;
        while (xsqr + ysqr < 4.0 && i++ < maxIterations)
        {
            zy *= zx;
            zy += zy + cy;
            zx = xsqr - ysqr + cx;
            xsqr = zx * zx;
            ysqr = zy * zy;
            if (i % 20 == 0)
            {   
                if (xsqr - oldz.x < 1e-12 && ysqr - oldz.y < 1e-12)
                {
                    i = maxIterations;
                    break;
                }
                oldz.x = xsqr;
                oldz.y = ysqr;
            }
        }
        x++;
    }
    end = clock(); // Fin du chronomètre
    elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC; // Calcul du temps écoulé
    printf("Résultat1: %d, Temps d'exécution: %f secondes\n", i, elapsed_time);


    x = 0;
    double complex c;
    double complex z;
    t_dvector oldz2;
    // t_dvector old_z;
    // t_dvector old_z2;
    
    // old_z = (t_dvector){.x = 0.0, .y=0.0};
    start = clock(); // Début du chronomètre
    // old_z2 = (t_dvector){.x = creal(z), .y = cimag(z)};
    while (x < 640000)
    {
        c = -0.786 + 0.268 * I;
        z = 0;
        i = 0;
        oldz = (t_dvector){.x = 0.0, .y=0.0};
        while (cabs(z) <= 2.0 && i++ < maxIterations)
        {
            z = z * z + c;
            if (i % 20 == 0)
            {
                oldz2 = (t_dvector){.x = creal(z), .y = cimag(z)};
                if (fabs(oldz2.x - oldz.x) < 1e-6 && fabs(oldz2.y - oldz.y) < 1e-6)
                {
                    i = maxIterations;
                    break;
                }
                oldz.x = oldz2.x;
                oldz.y = oldz2.y;
            }
        }
        x++;
    }
    end = clock(); // Fin du chronomètre
    elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC; // Calcul du temps écoulé
    printf("Résultat2: %d, Temps d'exécution: %f secondes\n", i, elapsed_time);


    x = 0;
    start = clock(); // Début du chronomètre
    while (x < 640000)
    {
        cx = -0.786;
        cy = 0.268;
        zx = 0.0;
        zy = 0.0;
        xsqr = 0.0;
        ysqr = 0.0;
        oldz = (t_dvector){.x = 0.0, .y=0.0};
        i = 0;
        while (xsqr + ysqr < 4.0 && i++ < maxIterations)
        {
            zy *= zx;
            zy += zy + cy;
            zx = xsqr - ysqr + cx;
            xsqr = zx * zx;
            ysqr = zy * zy;
            if (i % 20 == 0)
            {
                oldz2 = (t_dvector){.x = creal(z), .y = cimag(z)};
                if (fabs(oldz2.x - oldz.x) < 1e-6 && fabs(oldz2.y - oldz.y) < 1e-6)
                {
                    i = maxIterations;
                    break;
                }
                oldz.x = oldz2.x;
                oldz.y = oldz2.y;
            }
        }
        x++;
    }
    end = clock(); // Fin du chronomètre
    elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC; // Calcul du temps écoulé
    printf("Résultat1: %d, Temps d'exécution: %f secondes\n", i, elapsed_time);

    double cr = -0.786;  // Partie réelle de c
    double ci = 0.268;   // Partie imaginaire de c
    double zr = 0.0;   // Partie réelle de z
    double zi = 0.0;   // Par+tie imaginaire de z
    double temp;
    t_dvector zsqr;
    i = 0;

    start = clock(); // Début du chronomètre
    x = 0;
    while (x < 640000)
    {
        cr = -0.1;  // Partie réelle de c
        ci = 0.0;   // Partie imaginaire de c
        zr = 0.0;   // Partie réelle de z
        zi = 0.0;   // Partie imaginaire de z
        i = 0;
        zsqr = (t_dvector){.x = 0.0, .y=0.0};
        oldz = (t_dvector){.x = 0.0, .y=0.0};
        while ((zr * zr + zi * zi) < 4.0 && i < maxIterations) {
            temp = zr * zr - zi * zi + cr;
            zi = 2.0 * zr * zi + ci;
            zr = temp;

            if (i % 20 == 0) {
                if ( (zr - oldz.x) * (zr - oldz.x) < 1e-12 && (zi - oldz.y) *  (zi - oldz.y) < 1e-12) {
                    i = maxIterations;
                    break;
                }
                oldz.x = zr;
                oldz.y = zi;
            }
            i++;
        }
        x++;
    }
    end = clock(); // Fin du chronomètre
    elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC; // Calcul du temps écoulé
    printf("Résultat1: %d, Temps d'exécution: %f secondes\n", i, elapsed_time);
    return 0;
}



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
