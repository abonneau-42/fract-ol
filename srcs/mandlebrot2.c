/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandlebrot2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:08:02 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/10 05:34:12 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

typedef struct s_complex{
    double real;
    double imag;
} t_complex;

typedef struct {
    double delta_n;
    int n;
} t_result;

typedef struct s_ref_point_const{
	double complex	a[MAX_ITER];
	double complex  b[MAX_ITER];
	double complex  c[MAX_ITER];
	double complex  x[MAX_ITER];
	double complex  c0;
} t_ref_point_const;

static inline void my_mlx_pixel_put(t_data *data, unsigned int x, unsigned int y, unsigned int color)
{
    *(unsigned int*)(data->addr + (y * data->line_length + x * 4)) = color;
}

t_complex complex_mul(t_complex a, t_complex b) {
    t_complex result;
    result.real = a.real * b.real - a.imag * b.imag;
    result.imag = a.real * b.imag + a.imag * b.real;
    return result;
}

t_complex complex_pow(t_complex a, double pow) {
    t_complex result;
	unsigned int i;

	i = 1;
	result = a;
	while (i < pow)
	{
		result = complex_mul(result, result);
		i++;
	}
    return result;
}

t_complex complex_scale(t_complex a, double scale) {
    return ((t_complex){a.real * scale, a.imag * scale});
}

// Addition de deux nombres complexes
t_complex complex_add(t_complex a, t_complex b) {
    t_complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}

t_ref_point_const precalc_coefficients(double complex c0)
{

	t_ref_point_const refp;

	// refp.a[0] = (t_complex) {1, 0};
	// refp.b[0] = (t_complex) {0, 0};
	// refp.c[0] = (t_complex) {0, 0};
	// refp.x[0] = (t_complex) {0, 0};

	refp.a[0] = 1;
	refp.b[0] = 0;
	refp.c[0] = 0;
	refp.x[0] = 0;
	refp.c0 = 0.1 + 0.1 * I;
	// printf("c0-real: %f\n", creal(c0));
	// printf("c0-img: %f\n", cimag(c0));
	// printf("refp.c0-real: %f\n", creal(refp.x[0]));
	// printf("refp.c0-cimag: %f\n", cimag(refp.x[0]));
	// printf("refp.c0-real: %f\n", creal(refp.c0));
	// printf("refp.c0-cimag: %f\n", cimag(refp.c0));
	double complex c = 0.0 + 0.0 * I;
	double complex x = 0;

// int i = 0;
// 	while (cabs(x) < 2.0 && i < MAX_ITER)
// 	{
// 		x = x * x + c;
// 		i++;
// 	}

// 	printf("x: [%f,%f]\n", creal(x), cimag(x));
// 	printf ("i: %d\n", i);
	
    for (int n = 1; n < MAX_ITER; n++) {
		// refp.x[n] = complex_add(complex_pow(refp.x[n - 1], 2), c0);
		// refp.a[n] = complex_add(complex_mul(complex_scale(refp.x[n - 1], 2), refp.a[n - 1]), (t_complex) {1, 0});
		// refp.b[n] = complex_add(complex_mul(complex_scale(refp.x[n - 1], 2), refp.b[n - 1]), complex_mul(refp.a[n - 1], refp.a[n - 1]));
		// refp.c[n] = complex_add(complex_mul(complex_scale(refp.x[n - 1], 2), refp.c[n - 1]), complex_mul(complex_scale(refp.a[n - 1], 2), refp.b[n - 1]));
		
		// x = x * x + c;
		// printf("x: [%f,%f]\n", creal(x), cimag(x));

		refp.x[n] = refp.x[n - 1] * refp.x[n - 1] + refp.c0;
		// printf("refp.x[n]: %f\n", creal(refp.x[n]));
		refp.a[n] = 2 * refp.x[n - 1] * refp.a[n - 1] + 1;
		refp.b[n] = 2 * refp.x[n - 1] * refp.b[n - 1] + refp.a[n - 1] * refp.a[n - 1];
		refp.c[n] = 2 * refp.x[n - 1] * refp.c[n - 1] + 2 * refp.a[n - 1] * refp.b[n - 1];
    }

	
	return (refp);
}

t_cache set_point_in_cache_nothread(t_vars *ctx)
{
    t_cache cache;
    const t_dvector offset = {
        .x = 1.5 * ctx->zoom_x,
        .y = 1.5 * ctx->zoom_y
    };
    t_vector p;
    static int const half_screen_width = SCREEN_HEIGHT / 2;
    
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

t_bool diverges(t_complex delta_n, t_complex c) {
    if ((delta_n.real * delta_n.real + delta_n.imag * delta_n.imag) > 4.0) {
        return TRUE;
    }
    return FALSE;
}


// int dicho_search(t_complex c, t_ref_point_const refp)
// {
//     int n_min = 0;
//     int n_max = MAX_ITER - 1;
// 	t_complex	delta_n;

//     t_complex delta_0 = complex_add(c, complex_scale(refp.c0, -1));
    
//     while (n_min <= n_max) {
//         int n_middle = (n_min + n_max) / 2;
        
// 		delta_n = complex_add( complex_add(complex_mul(refp.a[n_middle], delta_0), complex_mul(refp.b[n_middle], complex_pow(delta_0, 2))), complex_mul(refp.c[n_middle], complex_pow(delta_0, 3)));

// 		if (diverges(delta_n, c)) {
// 			n_max = n_middle - 1;
// 		} else {
// 			n_min = n_middle + 1;
// 		}
// 	}
// 	return (n_max);
// }

// int dicho_search(double complex c, t_ref_point_const refp)
// {
//     int n_min = 0;
//     int n_max = MAX_ITER;
// 	int n_middle;
//     // t_complex delta_n;
// 	// t_complex x;

//     // t_complex delta_0 = complex_add(c, complex_scale(refp.c0, -1));

// 	double complex x = 0;
// 	double complex delta_n;
// 	double complex delta_0 = c - refp.c0;

// 	printf("c.real: %f, c.imag: %f\n", creal(c), cimag(c));
		

// 	// printf("delta_0.real: %f, delta_0.imag: %f\n", creal(delta_0), cimag(delta_0));

//     // Améliorer la condition de divergence
// 	// n_middle = 0;
// 	// while ((creal(x) * creal(x) + cimag(x) * cimag(x)) > 4.0 && n_middle < MAX_ITER)
// 	// {
// 	// 	delta_n = refp.a[n_middle] * delta_0 + refp.b[n_middle] * delta_0 * delta_0 + refp.c[n_middle] * delta_0 * delta_0 * delta_0;
// 	// 	x = refp.x[n_middle] + delta_n;
// 	// 	n_middle++;
// 	// }
// 	// return (n_middle);
	
//     while (n_min <= n_max) {
//         n_middle = (n_min + n_max) / 2;

// 		// printf ("-------------\n");
// 		// printf ("n_middle: %d\n", n_middle);
// 		// printf ("n_middle: %f\n", creal(refp.x[3]));

//         // Calcul du delta_n pour le middle actuel
//         //t_complex temp = complex_add(complex_mul(refp.a[n_middle], delta_0), (t_complex){0, 0});
// 		// printf("ok=%f\n", (double)(complex_mul(refp.a[n_middle], delta_0).real));

		
//         // delta_n = complex_add(
//         //     complex_add(complex_mul(refp.a[n_middle], delta_0),
//         //     complex_mul(refp.b[n_middle], complex_pow(delta_0, 2))),
//         //     complex_mul(refp.c[n_middle], complex_pow(delta_0, 3))
//         // );

// 		delta_n = refp.a[n_middle] * delta_0 + refp.b[n_middle] * delta_0 * delta_0 + refp.c[n_middle] * delta_0 * delta_0 * delta_0;

// 		// printf("delta_n.real: %f, delta_n.imag: %f\n", delta_n.real, delta_n.imag);
		
// 		// x = complex_add(refp.x[n_middle], delta_n);
// 		// printf("refp.x: %f, refp.x: %f\n", creal(refp.x[n_middle]), cimag(refp.x[n_middle]));
// 		// printf("delta_n.real: %f, delta_n.imag: %f\n", creal(delta_n), cimag(delta_n));

// 		x = refp.x[n_middle] + delta_n;

// 		// printf("x.real: %f, x.imag: %f\n", creal(x), cimag(x));
	
//         // Condition de divergence : on vérifie si la norme de delta_n dépasse 4
//         if ((creal(x) * creal(x) + cimag(x) * cimag(x)) > 4.0) {
//             n_max = n_middle - 1;
//         } else {
//             n_min = n_middle + 1;
//         }
//     }
// 	return (n_max);
// }

int dicho_search(double complex c, t_ref_point_const refp) {
    int n_min = 0;
    int n_max = MAX_ITER - 1;  // Corrected: n_max should be MAX_ITER - 1
    int best_n = -1; // Keep track of the best 'n' found so far

    double complex delta_0 = c - refp.c0;

    while (n_min <= n_max) {
        int n_middle = (n_min + n_max) / 2;

        double complex delta_n = refp.a[n_middle] * delta_0 + refp.b[n_middle] * delta_0 * delta_0 + refp.c[n_middle] * delta_0 * delta_0 * delta_0;
        double complex x = refp.x[n_middle] + delta_n;

        // Check if the approximated point diverges *using the approximation*
        if (cabs(x) > 2.0) { // Using cabs for complex magnitude
            n_max = n_middle - 1;
        } else {
            // Approximation is still valid, but we want the LARGEST valid n
            best_n = n_middle;
            n_min = n_middle + 1;
        }
    }
    return best_n; // Return the best n found
}

int mandelbrot(t_vars *ctx) 
{
	t_cache cache;
	t_vector p;
	t_ref_point_const refp;
	unsigned int i;

	cache = set_point_in_cache_nothread(ctx);
    refp = precalc_coefficients(cache.cached_x[0] + cache.cached_y[0] * I);
	p.y = 0;
	while (p.y < SCREEN_HEIGHT)
    {
		p.x = 0;
        while (p.x < SCREEN_WIDTH)
        {
			i = dicho_search(cache.cached_x[p.x] + cache.cached_y[p.y] * I, refp);

			if (i != -1)
            {
                my_mlx_pixel_put(&ctx->img, p.x, p.y, i * COLOR_RANGE); // No need to subtract MAX_ITER
            }
            else
            {
                my_mlx_pixel_put(&ctx->img, p.x, p.y, 0x000000); // Color for points that always diverge
            }
			// printf("[%d]", i - MAX_ITER);
			
			// my_mlx_pixel_put(&ctx->img, p.x, p.y, (i - MAX_ITER) * COLOR_RANGE);
			p.x++;
        }
		printf("\n");
        p.y++;
    }
    return 0;
}