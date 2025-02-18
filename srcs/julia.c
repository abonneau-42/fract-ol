/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:23:33 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/18 12:46:25 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include "fractol.h"

static inline void	my_mlx_pixel_put(t_data *data, unsigned int x,
		unsigned int y, unsigned int color)
{
	*(unsigned int*)(data->addr + (y * data->line_length + x * 4)) = color;
}

static inline unsigned int	find_color(const double x0,
		const double y0, double *c)
{
	unsigned int	i;
	t_dvector		oldz;
	t_dvector		z;
	double			temp;

	i = 0;
	oldz = (t_dvector){.x = x0, .y = y0};
	z = (t_dvector){.x = x0, .y = y0};
	while ((z.x * z.x + z.y * z.y) < 4.0 && i < MAX_ITER)
	{
		temp = z.x * z.x - z.y * z.y + c[0];
		z.y = 2.0 * z.x * z.y + c[1];
		z.x = temp;
		if (i % 20 == 0)
		{
			if ((z.x - oldz.x) * (z.x - oldz.x) < 1e-12
				&& (z.y - oldz.y) * (z.y - oldz.y) < 1e-12)
			{
				i = MAX_ITER;
				break ;
			}
			oldz.x = z.x;
			oldz.y = z.y;
		}
		i++;
	}
	return ((i - MAX_ITER) * COLOR_RANGE);
}

static inline void	compute_const_val_x(t_vars *ctx, t_dvector *const_val_x)
{
	const double	rate_x = JULIA_XMAX - JULIA_XMIN;
	double			offset_x;

	if (ctx->zoom_x > 0)
		offset_x = ctx->zoom_x * JULIA_XMIN;
	else
		offset_x = -(ctx->zoom_x * JULIA_XMAX);
	const_val_x->x = (rate_x / SCREEN_WIDTH) * ctx->zoom;
	const_val_x->y = ((rate_x * ctx->center_x) / SCREEN_WIDTH)
		* ctx->zoom + (ctx->zoom - 1) * 0.5 - offset_x + JULIA_XMIN * ctx->zoom;
}

static inline void	compute_const_val_y(t_vars *ctx, t_dvector *const_val_y)
{
	const double	rate_y = JULIA_YMAX - JULIA_YMIN;

	const_val_y->x = (rate_y / SCREEN_HEIGHT) * ctx->zoom;
	const_val_y->y = ((rate_y * ctx->center_y) / SCREEN_HEIGHT)
		* ctx->zoom + 1.5 * ctx->zoom_y + JULIA_YMIN * ctx->zoom;
}

void	julia(t_vars *ctx)
{
	t_vector	p;
	t_dvector	const_val_x;
	t_dvector	const_val_y;
	double		y0;
	double		cached_x[SCREEN_WIDTH];

	compute_const_val_x(ctx, &const_val_x);
	compute_const_val_y(ctx, &const_val_y);
	p = (t_vector){.x = 0, .y = 0};
	while (p.x < SCREEN_WIDTH)
	{
		cached_x[p.x] = const_val_x.y + p.x * const_val_x.x;
		p.x++;
	}
	while (p.y < SCREEN_HEIGHT)
	{
		y0 = const_val_y.y + p.y * const_val_y.x;
		p.x = 0;
		while (p.x < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(&ctx->img, p.x, p.y,
				find_color(cached_x[p.x], y0, (double *)&ctx->params));
			p.x++;
		}
		p.y++;
	}
}
