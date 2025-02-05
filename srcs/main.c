/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 07:48:48 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/05 16:16:14 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// void draw_axis(t_vars *ctx)
// {
//     int x = 0;
//     int y = 0;

//     // Calcul du centre des axes en tenant compte du zoom et du décalage
//     int axis_x = SCREEN_WIDTH / 2 - ctx->center_x;
//     int axis_y = SCREEN_HEIGHT / 2 - ctx->center_y;

//     // Dessin de l'axe horizontal (Y = 0)
//     if (axis_y >= 0 && axis_y < SCREEN_HEIGHT) // Vérifie qu'il est dans l'écran
//     {
//         while (x < SCREEN_WIDTH)
//         {
//             my_mlx_pixel_put(&ctx->img, x, axis_y, 0xFFFFFF);
//             x++;
//         }
//     }

//     // Dessin de l'axe vertical (X = 0)
//     if (axis_x >= 0 && axis_x < SCREEN_WIDTH) // Vérifie qu'il est dans l'écran
//     {
//         while (y < SCREEN_HEIGHT)
//         {
//             my_mlx_pixel_put(&ctx->img, axis_x, y, 0xFFFFFF);
//             y++;
//         }
//     }
// }

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
	// draw_axis(ctx);
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img.img, 0, 0);
}

int	key_hook(int keycode, t_vars *ctx)
{
	if (keycode == KEY_ESC)
		close_window(ctx);
	if (keycode == 65362)
	{
		ctx->center_y -= 10;
		redraw(ctx);
	}
	if (keycode == 65364)
	{
		ctx->center_y += 10;
		redraw(ctx);
	}
	if (keycode == 65361)
	{
		ctx->center_x -= 10;
		redraw(ctx);
	}
	if (keycode == 65363)
	{
		ctx->center_x += 10;
		redraw(ctx);
	}
	return (0);
}

int mouse_hook(int mousecode, int x, int y, t_vars *ctx)
{
	(void)x;
	(void)y;
	static double last_x = 0;
	static double last_y = 0;
	
    if (mousecode == 4)
        ctx->zoom *= 1.1;
    if (mousecode == 5)
    {
        ctx->zoom /= 1.1;
		last_x = last_x + ((((double)x / SCREEN_WIDTH) - 0.5) / 2) * ctx->zoom;
		last_y = last_y + ((((double)y / SCREEN_HEIGHT) - 0.5) / 2) * ctx->zoom;
		ctx->zoom_x = last_x;
		ctx->zoom_y = last_y;
    }
	redraw(ctx);
    return 0;
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

int	main(int argc, char **argv)
{
	t_vars	ctx;

	if (argc < 2)
	{
		write(1, "./fractol [julia|mandelbrot] [params]\n", 38);
		return (0);
	}
	if (ft_strcmp(argv[1], "julia") == 0)
	{
		if (check_number(argv[2], &ctx, 0) && check_number(argv[3], &ctx, 1))
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
	// ctx.zoom = 0.005;
	// ctx.zoom_x = 0.38;
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
	ctx.img.addr = mlx_get_data_addr(ctx.img.img, &ctx.img.bits_per_pixel, &ctx.img.line_length,
								&ctx.img.endian);
	ctx.fractal_fn(&ctx);
	// draw_axis(&ctx);
	mlx_put_image_to_window(ctx.mlx, ctx.win, ctx.img.img, 0, 0);
	mlx_key_hook(ctx.win, key_hook, &ctx);
	mlx_mouse_hook(ctx.win, mouse_hook, &ctx);
	mlx_hook(ctx.win, 17, 0, close_window, &ctx);
	mlx_loop(ctx.mlx);
}

