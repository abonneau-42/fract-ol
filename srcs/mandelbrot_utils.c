/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:45:53 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/19 11:06:10 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	compute_const_val_x_mdb(t_vars *ctx, t_dvector *const_val_x)
{
	const double	mandelbrot_dx = ((MANDELBROT_XMAX - MANDELBROT_XMIN)
			/ SCREEN_WIDTH);

	const_val_x->x = (ctx->center_x * mandelbrot_dx - (SCREEN_WIDTH / 2)
			* ctx->zoom * mandelbrot_dx + 1.5 * ctx->zoom_x + 1.5
			+ MANDELBROT_XMIN);
	const_val_x->y = ctx->zoom * mandelbrot_dx;
}

void	compute_const_val_y_mdb(t_vars *ctx, t_dvector *const_val_y)
{
	const double	mandelbrot_dy = ((MANDELBROT_YMAX - MANDELBROT_YMIN)
			/ SCREEN_HEIGHT);

	const_val_y->x = (ctx->center_y * mandelbrot_dy - (SCREEN_HEIGHT / 2)
			* ctx->zoom * mandelbrot_dy + 1.5 * ctx->zoom_y + 1.5
			+ MANDELBROT_YMIN);
	const_val_y->y = ctx->zoom * mandelbrot_dy;
}
