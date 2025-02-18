/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:23:33 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/18 15:28:38 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include "fractol.h"

static inline void	px_put(t_data *data, unsigned int x,
		unsigned int y, unsigned int color)
{
	*(unsigned int *)(data->addr + (y * data->line_length + x * 4)) = color;
}

static inline unsigned int	find_color(const double x0,
		const double y0, double *c)
{
	unsigned int	i;
	t_dvector		oldz;
	t_dvector		z;
	double			temp;

	i = 0;
	z = (t_dvector){.x = x0, .y = y0};
	oldz = z;
	while ((z.x * z.x + z.y * z.y) < 4.0 && i < MAX_ITER)
	{
		temp = z.x * z.x - z.y * z.y + c[0];
		z.y = 2.0 * z.x * z.y + c[1];
		z.x = temp;
		if (i++ % 20 == 0)
		{
			if ((z.x - oldz.x) * (z.x - oldz.x) < 1e-12
				&& (z.y - oldz.y) * (z.y - oldz.y) < 1e-12)
			{
				i = MAX_ITER;
				break ;
			}
			oldz = z;
		}
	}
	return ((i - MAX_ITER) * (16581375 / MAX_ITER));
}

void	julia(t_vars *ctx)
{
	t_vector	p;
	t_dvector	const_val_x;
	t_dvector	const_val_y;
	double		y0;
	double		x[SCREEN_WIDTH];

	compute_const_val_x_julia(ctx, &const_val_x);
	compute_const_val_y_julia(ctx, &const_val_y);
	p = (t_vector){.x = 0, .y = 0};
	while (p.x < SCREEN_WIDTH)
	{
		x[p.x] = const_val_x.y + p.x * const_val_x.x;
		p.x++;
	}
	while (p.y < SCREEN_HEIGHT)
	{
		y0 = const_val_y.y + p.y * const_val_y.x;
		p.x = 0;
		while (p.x < SCREEN_WIDTH)
		{
			px_put(&ctx->img, p.x, p.y, find_color(x[p.x], y0, ctx->params));
			p.x++;
		}
		p.y++;
	}
}
