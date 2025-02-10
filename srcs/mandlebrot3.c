// #include "fractol.h"

// typedef struct {
//     double complex *A_n;
//     double complex *B_n;
//     double complex *C_n;
// } ReferenceValues;

// static inline void my_mlx_pixel_put(t_data *data, unsigned int x, unsigned int y, unsigned int color)
// {
//     *(unsigned int*)(data->addr + (y * data->line_length + x * 4)) = color;
// }

// ReferenceValues precompute_reference_values(double complex reference_point, int max_iter) {
//     ReferenceValues ref_values;
//     ref_values.A_n = (double complex *)malloc(max_iter * sizeof(double complex));
//     ref_values.B_n = (double complex *)malloc(max_iter * sizeof(double complex));
//     ref_values.C_n = (double complex *)malloc(max_iter * sizeof(double complex));

//     double complex z = 0;
//     for (int n = 0; n < max_iter; n++) {
//         ref_values.A_n[n] = 2 * z;
//         ref_values.B_n[n] = 1;
//         ref_values.C_n[n] = 0;
//         z = z * z + reference_point;
//     }

//     return ref_values;
// }

// int mandelbrot_perturbation(double complex c, int max_iter, double complex reference_point, ReferenceValues ref_values) {
//     double complex z = 0;
//     double complex delta_0 = c - reference_point;

//     for (int n = 0; n < max_iter; n++) {
//         double complex delta_n = ref_values.A_n[n] * delta_0 + ref_values.B_n[n] * delta_0 * delta_0 + ref_values.C_n[n] * delta_0 * delta_0 * delta_0;
//         z = z * z + c;

//         if (cabs(z) > 2) {
//             return n;
//         }
//     }

//     return max_iter;
// }

// void free_reference_values(ReferenceValues ref_values) {
//     free(ref_values.A_n);
//     free(ref_values.B_n);
//     free(ref_values.C_n);
// }

// int mandelbrot(t_vars *ctx) {
// 	t_vector p;
//     double complex reference_point = -0.75 + 0.1 * I;
//     ReferenceValues ref_values = precompute_reference_values(reference_point, MAX_ITER);

//     // double complex c = -0.74 + 0.8 * I;

// 	p.y = 0;
// 	while (p.y < 800)
// 	{
// 		p.x = 0;
// 		while (p.x < 800)
// 		{
// 			double real = -1.5 + (p.x / 800.0) * 3.0;
// 			double imag = -1.5 + (p.y / 800.0) * 3.0;
// 			double complex c = real + imag * I;
// 			int iterations = mandelbrot_perturbation(c, MAX_ITER, reference_point, ref_values);/*  */
// 			if (iterations == MAX_ITER)
// 				my_mlx_pixel_put(&ctx->img, p.x, p.y, 0xFFFFFF);
// 			else
// 				my_mlx_pixel_put(&ctx->img, p.x, p.y, 0x000000 + iterations * 1000);
// 			p.x++;
// 		}
// 		p.y++;
// 	}
//     free_reference_values(ref_values);
//     return 0;
// }
