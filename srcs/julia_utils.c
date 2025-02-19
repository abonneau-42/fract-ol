/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:51:38 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/19 11:12:02 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	compute_const_val_x_julia(t_vars *ctx, t_dvector *const_val_x)
{
	const double	rate_x = JULIA_XMAX - JULIA_XMIN;
	double			offset_x;

	if (ctx->zoom_x > 0)
		offset_x = ctx->zoom_x * JULIA_XMIN;
	else
		offset_x = -(ctx->zoom_x * JULIA_XMAX);
	const_val_x->x = (rate_x / SCREEN_WIDTH) * ctx->zoom;
	const_val_x->y = ((rate_x * ctx->center_x) / SCREEN_WIDTH)
		+ (ctx->zoom - 1) * 0.5 - offset_x + JULIA_XMIN * ctx->zoom;
}

void	compute_const_val_y_julia(t_vars *ctx, t_dvector *const_val_y)
{
	const double	rate_y = JULIA_YMAX - JULIA_YMIN;

	const_val_y->x = (rate_y / SCREEN_HEIGHT) * ctx->zoom;
	const_val_y->y = ((rate_y * ctx->center_y) / SCREEN_HEIGHT)
		+ 1.5 * ctx->zoom_y + JULIA_YMIN * ctx->zoom;
}
