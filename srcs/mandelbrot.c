/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:32:46 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/18 14:47:19 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline void	my_mlx_pixel_put(t_data *data, unsigned int x,
		unsigned int y, unsigned int color)
{
	*(unsigned int*)(data->addr + (y * data->line_length + x * 4)) = color;
}

static inline unsigned int	find_color(const double x0, const double y0)
{
	t_dvector	oldz;
	t_dvector	z;
	double		temp;
	int			i;

	oldz = (t_dvector){.x = 0.0, .y = 0.0};
	z = (t_dvector){.x = 0.0, .y = 0.0};
	i = 0;
	while ((z.x * z.x + z.y * z.y) < 4.0 && i < MAX_ITER)
	{
		temp = z.x * z.x - z.y * z.y + x0;
		z.y = 2.0 * z.x * z.y + y0;
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
	return ((i - MAX_ITER) * (16581375 / MAX_ITER));
}

static inline int	optimise_render(const t_vector p, const t_dvector y0,
		const double x0, t_vars *ctx)
{
	const double	xv0 = (x0 - 0.25);
	const double	q = xv0 * xv0 + y0.y;

	if (q * (q + xv0) < 0.25 * y0.y || (x0 + 1) * (x0 + 1) + y0.y < 0.0625)
	{
		my_mlx_pixel_put(&ctx->img, p.x, p.y, 0);
		return (1);
	}
	my_mlx_pixel_put(&ctx->img, p.x, p.y, find_color(x0, y0.x));
	return (0);
}

static t_cache	set_point_in_cache(t_vars *ctx)
{
	t_cache			cache;
	t_dvector		const_val_x;
	t_dvector		const_val_y;
	unsigned int	i;

	compute_const_val_x_mdb(ctx, &const_val_x);
	compute_const_val_y_mdb(ctx, &const_val_y);
	i = 0;
	while (i < SCREEN_WIDTH)
	{
		cache.cached_x[i] = (int)i * const_val_x.y + const_val_x.x;
		i++;
	}
	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		cache.cached_y[i] = (int)i * const_val_y.y + const_val_y.x;
		i++;
	}
	return (cache);
}

void	mandelbrot(t_vars *ctx)
{
	t_vector	p;
	t_dvector	y0;
	t_cache		cache;

	cache = set_point_in_cache(ctx);
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
				continue ;
			}
			p.x++;
		}
		p.y++;
	}
}
