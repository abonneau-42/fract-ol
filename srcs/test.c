// #include "fractol.h"

// // Définir une structure pour représenter un nombre complexe
// typedef struct {
//     double real;
//     double imag;
// } Complex;

// // Fonction pour calculer le module d'un nombre complexe
// double module(Complex z) {
//     return sqrt(z.real * z.real + z.imag * z.imag);
// }

// static inline void my_mlx_pixel_put(t_data *data, unsigned int x, unsigned int y, unsigned int color)
// {
//     *(unsigned int*)(data->addr + (y * data->line_length + x * 4)) = color;
// }

// // Fonction pour l'itération de Mandelbrot avec perturbation de Kalles Fraktaler
// int mandelbrot_with_perturbation(Complex c, int max_iter, double perturbation_factor) {
//     Complex z = {0.0, 0.0};
//     int iter = 0;

//     // Itération avec perturbation
//     while (iter < max_iter) {
//         double perturbation = sin(z.real + z.imag) * perturbation_factor;
        
//         // Applique la perturbation à la partie réelle de l'itération
//         z.real = z.real * z.real - z.imag * z.imag + c.real + perturbation;
//         z.imag = 2 * z.real * z.imag + c.imag;

//         if (module(z) > 2.0) {
//             return iter;
//         }
//         iter++;
//     }
//     return iter;
// }

// // Fonction principale pour générer l'ensemble de Mandelbrot
// void generate_mandelbrot(int width, int height, double x_min, double x_max, double y_min, double y_max, int max_iter, double perturbation_factor, t_vars *ctx) {
//     for (int y = 0; y < height; y++) {
//         for (int x = 0; x < width; x++) {
//             // Calculer les coordonnées complexes en fonction des dimensions de l'écran
//             double real = x_min + (x / (double)width) * (x_max - x_min);
//             double imag = y_min + (y / (double)height) * (y_max - y_min);
            
//             Complex c = {real, imag};
//             int iter = mandelbrot_with_perturbation(c, max_iter, perturbation_factor);
            
//             // Afficher un caractère en fonction du nombre d'itérations (pour visualisation)
//             if (iter == max_iter) {
// 				my_mlx_pixel_put(&ctx->img, x, y, 0xFFFFFF);
//             } else {
//                 my_mlx_pixel_put(&ctx->img, x, y, 0x000000 + iter * 1000);
//             }
//         }
//     }
// }

// int mandelbrot(t_vars *ctx) {
//     int width = 800;  // Largeur de l'image (caractères)
//     int height = 800; // Hauteur de l'image (caractères)
//     int max_iter = 1000;  // Nombre d'itérations
//     double perturbation_factor = 0.000001; // Facteur de perturbation

//     // Plage de coordonnées complexes pour l'ensemble de Mandelbrot
//     double x_min = -2.0, x_max = 1.0, y_min = -1.5, y_max = 1.5;

//     // Générer et afficher l'ensemble de Mandelbrot avec perturbation
//     generate_mandelbrot(width, height, x_min, x_max, y_min, y_max, max_iter, perturbation_factor, ctx);

//     return 0;
// }
