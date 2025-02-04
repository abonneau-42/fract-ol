/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:32:46 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/04 12:38:11 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// int



// // int mandelbrot(t_vars *ctx)
// // {
// //     // Calculer les incréments dx et dy en fonction du zoom
// //     double dx = (MANDELBROT_XMAX - MANDELBROT_XMIN) / (SCREEN_WIDTH * ctx->zoom);
// //     double dy = (MANDELBROT_YMAX - MANDELBROT_YMIN) / (SCREEN_HEIGHT * ctx->zoom);

// //     // Calculer le centre du zoom en coordonnées réelles
// //     // (ctx->zoom_x, ctx->zoom_y) sont les coordonnées du point observé (en pixels)
// //     double center_x = MANDELBROT_XMIN + ((ctx->zoom_x) / SCREEN_WIDTH) * (MANDELBROT_XMAX - MANDELBROT_XMIN);
// //     double center_y = MANDELBROT_YMIN + ((ctx->zoom_y) / SCREEN_HEIGHT) * (MANDELBROT_YMAX - MANDELBROT_YMIN);

// //     int py = 0;
// //     int px = 0;

// //     // Créer un tableau pour les pixels
// //     unsigned int *pixels = (unsigned int *)malloc(sizeof(unsigned int) * SCREEN_WIDTH * SCREEN_HEIGHT);

// //     // Parcourir tous les pixels de l'écran
// //     while (py < SCREEN_HEIGHT)
// //     {
// //         px = 0;
// //         while (px < SCREEN_WIDTH)
// //         {
// //             // Calculer les coordonnées x0 et y0 pour chaque pixel en fonction du zoom et du centre observé
// //             double x0 = center_x + px * dx;  // Décalage pour centrer sur le point zoomé
// //             double y0 = center_y + py * dy; // Décalage pour centrer sur le point zoomé

// //             // Initialisation des variables pour l'itération de Mandelbrot
// //             double complex c = x0 + y0 * I;
// //             double complex z = 0;
// //             int iter = 0;

// //             // Calcul de la fractale de Mandelbrot
// //             while (cabs(z) <= 2.0 && iter < MAX_ITER) {
// //                 z = z * z + c;
// //                 iter++;
// //             }

// //             // Calcul de la couleur en fonction du nombre d'itérations
// //             int color = (iter == MAX_ITER) ? 0 : (iter * 255 / MAX_ITER);

// //             // Stocker la couleur dans le buffer
// //             pixels[py * SCREEN_WIDTH + px] = color;

// //             px++;
// //         }
// //         py++;
// //     }

// //     // Copier le contenu du buffer dans l'image
// //     for (int i = 0; i < SCREEN_HEIGHT; i++) {
// //         for (int j = 0; j < SCREEN_WIDTH; j++) {
// //             my_mlx_pixel_put(&ctx->img, j, i, pixels[i * SCREEN_WIDTH + j]);
// //         }
// //     }

// //     // Libérer le buffer
// //     free(pixels);

// //     return (0);
// // }



// // int mandelbrot(t_vars *ctx)
// // {
// //     // Calcul des nouveaux incréments dx et dy en fonction du zoom
// //     double dx = (MANDELBROT_XMAX - MANDELBROT_XMIN) / (SCREEN_WIDTH * ctx->zoom);
// //     double dy = (MANDELBROT_YMAX - MANDELBROT_YMIN) / (SCREEN_HEIGHT * ctx->zoom);

// //     int py = 0;
// //     int px = 0;

// //     // Parcourir tous les pixels de l'écran
// //     while (py < SCREEN_HEIGHT)
// //     {
// //         px = 0;
// //         while (px < SCREEN_WIDTH)
// //         {
// //             // Calcul des coordonnées x0 et y0 pour chaque pixel
// //             // (ctx->zoom_x et ctx->zoom_y deviennent le centre du zoom)
// //             double x0 = (ctx->zoom_x / SCREEN_WIDTH) + (px - SCREEN_WIDTH / 2) * dx;
// //             double y0 = (ctx->zoom_y / SCREEN_HEIGHT) + (py - SCREEN_HEIGHT / 2) * dy;

// //             // Initialisation des variables de la fractale
// //             double complex c = x0 + y0 * I;
// //             double complex z = 0;
// //             int iter = 0;

// //             // Calcul de la fractale de Mandelbrot
// //             while (cabs(z) <= 2.0 && iter < MAX_ITER) {
// //                 z = z * z + c;
// //                 iter++;
// //             }

// //             // Calcul de la couleur en fonction du nombre d'itérations
// //             int color = (iter == MAX_ITER) ? 0 : (iter * 255 / MAX_ITER);
// //             my_mlx_pixel_put(&ctx->img, px, py, color);

// //             px++;
// //         }
// //         py++;
// //     }

// //     return (0);
// // }


// // int mandelbrot(t_vars *ctx)
// // {
// //     // Calcul des nouveaux incréments dx et dy en fonction du zoom
// //     double dx = (MANDELBROT_XMAX - MANDELBROT_XMIN) / (SCREEN_WIDTH * ctx->zoom);
// //     double dy = (MANDELBROT_YMAX - MANDELBROT_YMIN) / (SCREEN_HEIGHT * ctx->zoom);

// //     int py = 0;
// //     int px = 0;

// //     // Convertir zoom_x, zoom_y (en pixels) en coordonnées de l'ensemble Mandelbrot
// //     // double center_x = (ctx->zoom_x - SCREEN_WIDTH / 2);
// //     // double center_y = (ctx->zoom_y - SCREEN_HEIGHT / 2);

// //     // Parcourir tous les pixels de l'écran
// //     while (py < SCREEN_HEIGHT)
// //     {
// //         px = 0;
// //         while (px < SCREEN_WIDTH)
// //         {
// //             // Calculer les coordonnées x0 et y0 pour chaque pixel en fonction du zoom
// //             // Le zoom est centré sur (center_x, center_y) dans l'ensemble de Mandelbrot
// //             double x0 = px - SCREEN_WIDTH / 2 * dx;
// //             double y0 = py - SCREEN_HEIGHT / 2 * dy;

// //             // Initialisation des variables de la fractale
// //             double complex c = x0 + y0 * I;
// //             double complex z = 0;
// //             int iter = 0;

// //             // Calcul de la fractale de Mandelbrot
// //             while (cabs(z) <= 2.0 && iter < MAX_ITER) {
// //                 z = z * z + c;
// //                 iter++;
// //             }

// //             // Calcul de la couleur en fonction du nombre d'itérations
// //             int color = (iter == MAX_ITER) ? 0 : (iter * 255 / MAX_ITER);
// //             my_mlx_pixel_put(&ctx->img, px, py, color);

// //             px++;
// //         }
// //         py++;
// //     }

// //     return (0);
// // }



// // int mandelbrot(t_vars *ctx)
// // {
// //     // Calcul des nouvelles dimensions de l'ensemble Mandelbrot en fonction du zoom
// //     double dx = (MANDELBROT_XMAX - MANDELBROT_XMIN) / (SCREEN_WIDTH * ctx->zoom);
// //     double dy = (MANDELBROT_YMAX - MANDELBROT_YMIN) / (SCREEN_HEIGHT * ctx->zoom);
// //     int py = 0;
// //     int px = 0;

// //     // Calcul du centre de l'ensemble Mandelbrot (initialement centré au milieu)
// //     // double center_x = (MANDELBROT_XMAX + MANDELBROT_XMIN) / 2.0;
// //     // double center_y = (MANDELBROT_YMAX + MANDELBROT_YMIN) / 2.0;

// //     // Adapter le centre du zoom aux coordonnées passées (zoom_x, zoom_y)
// //     // double scale_x = (MANDELBROT_XMAX - MANDELBROT_XMIN) / (SCREEN_WIDTH * ctx->zoom);
// //     // double scale_y = (MANDELBROT_YMAX - MANDELBROT_YMIN) / (SCREEN_HEIGHT * ctx->zoom);

// //     // Déplacer le centre du zoom autour des coordonnées (zoom_x, zoom_y)
// //     // center_x = ctx->zoom_x;
// //     // center_y = ctx->zoom_y;

// //     while (py < SCREEN_HEIGHT)
// //     {
// //         while (px < SCREEN_WIDTH)
// //         {
// //             // Adapter les coordonnées en fonction du zoom et du centre ajusté
// //             double x0 = 0 + (px - SCREEN_WIDTH / 2.0) * dx;
// //             double y0 = 0 + (py - SCREEN_HEIGHT / 2.0) * dy;

// //             // Calcul de la fractale de Mandelbrot
// //             double complex c = x0 + y0 * I;
// //             double complex z = 0;
// //             int iter = 0;

// //             while (cabs(z) <= 2.0 && iter < MAX_ITER) {
// //                 z = z * z + c;
// //                 iter++;
// //             }

// //             // Calcul de la couleur en fonction du nombre d'itérations
// //             int color = (iter == MAX_ITER) ? 0 : (iter * 255 / MAX_ITER);
// //             my_mlx_pixel_put(&ctx->img, px, py, color);

// //             px++;
// //         }
// //         py++;
// //     }

// //     return (0);
// // }
