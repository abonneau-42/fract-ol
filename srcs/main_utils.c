/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:57:36 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/19 10:27:02 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_window(t_vars *ctx)
{
	mlx_destroy_image(ctx->mlx, ctx->img.img);
	mlx_destroy_window(ctx->mlx, ctx->win);
	mlx_destroy_display(ctx->mlx);
	free(ctx->mlx);
	exit(0);
}

void	redraw(t_vars *ctx)
{
	mlx_clear_window(ctx->mlx, ctx->win);
	ctx->fractal_fn(ctx);
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img.img, 0, 0);
}

int	key_hook(int keycode, t_vars *ctx)
{
	if (keycode == KEY_ESC)
		close_window(ctx);
	if (keycode == 65362)
		ctx->keyboard.arrow_top = TRUE;
	if (keycode == 65364)
		ctx->keyboard.arrow_bottom = TRUE;
	if (keycode == 65361)
		ctx->keyboard.arrow_left = TRUE;
	if (keycode == 65363)
		ctx->keyboard.arrow_right = TRUE;
	return (0);
}

int	mouse_hook(int mousecode, int x, int y, t_keyboard *keyboard)
{
	(void)x;
	(void)y;
	if (mousecode == 4)
		keyboard->scrollmouseup = TRUE;
	if (mousecode == 5)
		keyboard->scrollmousedown = TRUE;
	return (0);
}

void	parse_error_message(void)
{
	write(STDOUT_FILENO,
		"Usage: ./fractol [julia|mandelbrot] [?params1] [?params2]\n", 58);
	exit(0);
}
