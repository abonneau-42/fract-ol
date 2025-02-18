/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 07:48:48 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/18 15:10:31 by abonneau         ###   ########.fr       */
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

int	check_number(char *chr, t_vars *ctx, int index)
{
	double	value;

	if (!is_number(chr))
		return (0);
	if (ft_strlen(chr) > 11)
		return (0);
	value = ft_atof(chr);
	if (value < -2147483648 || value > 2147483647)
		return (0);
	ctx->params[index] = value;
	return (1);
}

int	render(t_vars *ctx)
{
	t_vector	cursor;

	if (ctx->keyboard.scrollmousedown == TRUE)
	{
		ctx->zoom *= 1.1;
		ctx->keyboard.scrollmousedown = FALSE;
		redraw(ctx);
	}
	else if (ctx->keyboard.scrollmouseup == TRUE)
	{
		mlx_mouse_get_pos(ctx->mlx,ctx->win, (int *)&cursor.x,
			(int *)&cursor.y);
		ctx->zoom_x += ((((double)cursor.x / SCREEN_WIDTH) - 0.5) * 2) * ctx->zoom * 0.2;
		ctx->zoom_y += ((((double)cursor.y / SCREEN_HEIGHT) - 0.5) * 2) * ctx->zoom * 0.2;
		ctx->zoom /= 1.1;
		ctx->keyboard.scrollmouseup = FALSE;
		redraw(ctx);
	}
	if (ctx->keyboard.arrow_left || ctx->keyboard.arrow_right
		|| ctx->keyboard.arrow_top || ctx->keyboard.arrow_bottom)
	{
		if (ctx->keyboard.arrow_left == TRUE)
			ctx->center_x -= 10;
		if (ctx->keyboard.arrow_right == TRUE)
			ctx->center_x += 10;
		if (ctx->keyboard.arrow_top == TRUE)
			ctx->center_y -= 10;
		if (ctx->keyboard.arrow_bottom == TRUE)
			ctx->center_y += 10;
		ctx->keyboard.arrow_left = FALSE;
		ctx->keyboard.arrow_right = FALSE;
		ctx->keyboard.arrow_top = FALSE;
		ctx->keyboard.arrow_bottom = FALSE;
		redraw(ctx);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	ctx;
	double params[2];
	ctx.params = params;

	if (argc < 2)
	{
		write(1, "./fractol [julia|mandelbrot] [params]\n", 38);
		return (0);
	}
	if (ft_strcmp(argv[1], "julia") == 0)
	{
		if (argv[2] && argv[3] && check_number(argv[2], &ctx, 0)
			&& check_number(argv[3], &ctx, 1))
			ctx.fractal_fn = julia;
		else
		{
			write(1, "./fractol [julia|mandelbrot] [params]\n", 38);
			return (0);
		}
	}
	else if (ft_strcmp(argv[1], "mandelbrot") == 0)
		ctx.fractal_fn = mandelbrot;
	else
	{
		write(1, "./fractol [julia|mandelbrot] [params]\n", 38);
		return (0);
	}
	ctx.keyboard = (t_keyboard){FALSE, FALSE, FALSE, FALSE,
		FALSE, FALSE, FALSE};
	ctx.zoom = 1;
	ctx.zoom_x = 0;
	ctx.center_x = 0;
	ctx.center_y = 0;
	ctx.zoom_y = 0;
	ctx.mlx = mlx_init();
	if (!ctx.mlx)
		exit(EXIT_FAILURE);
	ctx.win = mlx_new_window(ctx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, argv[1]);
	ctx.img.img = mlx_new_image(ctx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	ctx.img.addr = mlx_get_data_addr(ctx.img.img, &ctx.img.bits_per_pixel,
			&ctx.img.line_length,
			&ctx.img.endian);
	ctx.fractal_fn(&ctx);
	mlx_put_image_to_window(ctx.mlx, ctx.win, ctx.img.img, 0, 0);
	mlx_key_hook(ctx.win, key_hook, &ctx);
	mlx_mouse_hook(ctx.win, mouse_hook, &ctx.keyboard);
	mlx_hook(ctx.win, 17, 0, close_window, &ctx);
	mlx_loop_hook(ctx.mlx, render, &ctx);
	mlx_loop(ctx.mlx);
}
