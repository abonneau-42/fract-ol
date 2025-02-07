/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 07:48:48 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/07 23:27:07 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void my_mlx_pixel_put(t_data *data, unsigned int x, unsigned int y, unsigned int color)
{
    *(unsigned int*)(data->addr + (y * data->line_length + x * (data->bits_per_pixel >> 3))) = color;
}

void draw_axis(t_vars *ctx)
{
    int x = 0;
    int y = 0;

    // Calcul du centre des axes en tenant compte du zoom et du décalage
    int axis_x = SCREEN_WIDTH / 2 - ctx->center_x;
    int axis_y = SCREEN_HEIGHT / 2 - ctx->center_y;

    // Dessin de l'axe horizontal (Y = 0)
    if (axis_y >= 0 && axis_y < SCREEN_HEIGHT) // Vérifie qu'il est dans l'écran
    {
        while (x < SCREEN_WIDTH)
        {
            my_mlx_pixel_put(&ctx->img, x, axis_y, 0xFFFFFF);
            x++;
        }
    }

    // Dessin de l'axe vertical (X = 0)
    if (axis_x >= 0 && axis_x < SCREEN_WIDTH) // Vérifie qu'il est dans l'écran
    {
        while (y < SCREEN_HEIGHT)
        {
            my_mlx_pixel_put(&ctx->img, axis_x, y, 0xFFFFFF);
            y++;
        }
    }
}

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
	draw_axis(ctx);
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

int mouse_hook(int mousecode, int x, int y, t_keyboard *keyboard)
{
	if (mousecode == 4)
		keyboard->scrollmouseup = TRUE;
	if (mousecode == 5)
		keyboard->scrollmousedown = TRUE;
	keyboard->cursor = (t_vector){.x = x, .y = y};
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
	// static t_dvector zoompos = {
	// 	.x = MANDELBROT_XMIN + (MANDELBROT_XMAX - MANDELBROT_XMIN) * 0.5, 
	// 	.y = MANDELBROT_YMIN + (MANDELBROT_YMAX - MANDELBROT_YMIN) * 0.5
	// };

	static t_dvector zoompos = {
		.x = 0, 
		.y = 0
	};
	
	static double last_x = 0;
	static double last_y = 0;
	
    if (ctx->keyboard.scrollmousedown == TRUE)
	{
		ctx->zoom *= 1.1;
		// last_x = last_x + ((((double)ctx->keyboard.cursor.x / SCREEN_WIDTH) - 0.68)) * ctx->zoom;
		// last_y = last_y + ((((double)ctx->keyboard.cursor.y / SCREEN_HEIGHT) - 0.59)) * ctx->zoom;

		// printf("last_x: %f\n", ((((double)ctx->keyboard.cursor.x / SCREEN_WIDTH) - 0.5)) * ctx->zoom);
		// printf("last_y: %f\n", ((((double)ctx->keyboard.cursor.y / SCREEN_HEIGHT) - 0.5)) * ctx->zoom);
		// ctx->zoom_x = last_x;
		// ctx->zoom_y = last_y;
		// printf("zoom_x: %f\n", ctx->zoom_x);
		// printf("zoom_y: %f\n", ctx->zoom_y);
		ctx->keyboard.scrollmousedown = FALSE;
		redraw(ctx);
	}
	else if (ctx->keyboard.scrollmouseup == TRUE)
    {
		// double x = (((double)ctx->keyboard.cursor.x / SCREEN_WIDTH) * (MANDELBROT_XMAX - MANDELBROT_XMIN) - 1.5) * ctx->zoom;
		// double y = (((double)ctx->keyboard.cursor.y / SCREEN_HEIGHT) * (MANDELBROT_YMAX - MANDELBROT_YMIN) - 1.5) * ctx->zoom;
		
		// double x = (((double)ctx->keyboard.cursor.x / SCREEN_WIDTH) - 0.5) * 2;
		// double y = (((double)ctx->keyboard.cursor.y / SCREEN_HEIGHT) - 0.5) * 2;

		// zoompos.x = x - ctx->zoom_x;
		// zoompos.y = y - ctx->zoom_y;

		double x = 0;
		double y = 0;

		ctx->zoom_x += x * ctx->zoom;
		ctx->zoom_y += y * ctx->zoom;

		printf("vecteur direction: [%f, %f]\n", x, y);
		printf("zoom pos: [%f, %f]\n", ctx->zoom_x, ctx->zoom_y);

		// printf("zoompos.x: %f\n", zoompos.x);
		// printf("zoompos.y: %f\n", zoompos.y);

		// printf("zoom_x: %f\n", ctx->zoom_x);
		// printf("zoom_y: %f\n", ctx->zoom_y);

		// getposition cursor
		// x = (double)ctx->keyboard.cursor.x / SCREEN_WIDTH
		// y = (double)ctx->keyboard.cursor.y / SCREEN_HEIGHT

		// realzoomx = MANDELBROT_XMIN + (MANDELBROT_XMAX - MANDELBROT_XMIN) * 0.5;
		// realzoomy = MANDELBROT_YMIN + (MANDELBROT_YMAX - MANDELBROT_YMIN) * 0.5;


		

		// last_x 

		// last_x = last_x + x * ctx->zoom;
		// last_y = last_x + y * ctx->zoom;
		
		
		
		
		// last_x = last_x + ((ctx->keyboard.cursor.x / (double)SCREEN_WIDTH) * (MANDELBROT_XMAX - MANDELBROT_XMIN) + MANDELBROT_XMIN) * ctx->zoom;
		// last_y = last_y + ((ctx->keyboard.cursor.y / (double)SCREEN_HEIGHT) * (MANDELBROT_YMAX - MANDELBROT_YMIN) + MANDELBROT_YMIN) * ctx->zoom;


		// // printf("last_x: %f\n", ((((double)ctx->keyboard.cursor.x / SCREEN_WIDTH) - 0.5)) * ctx->zoom);
		// // printf("last_y: %f\n", ((((double)ctx->keyboard.cursor.y / SCREEN_HEIGHT) - 0.5)) * ctx->zoom);
		// ctx->zoom_x = last_x;
		// ctx->zoom_y = last_y;
		// draw_axis(ctx);
		// printf("zoom_x: %f\n", ctx->zoom_x);
		// printf("zoom_y: %f\n", ctx->zoom_y);
		ctx->zoom /= 1.1;
		ctx->keyboard.scrollmouseup = FALSE;
		redraw(ctx);
    }
	if (ctx->keyboard.arrow_left || ctx->keyboard.arrow_right || ctx->keyboard.arrow_top || ctx->keyboard.arrow_bottom)
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

	if (argc < 2)
	{
		write(1, "./fractol [julia|mandelbrot] [params]\n", 38);
		return (0);
	}
	if (ft_strcmp(argv[1], "julia") == 0)
	{
		if (argv[2] && argv[3] && check_number(argv[2], &ctx, 0) && check_number(argv[3], &ctx, 1))
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

	ctx.keyboard = (t_keyboard){FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, (t_vector){0, 0}};
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
	draw_axis(&ctx);
	mlx_put_image_to_window(ctx.mlx, ctx.win, ctx.img.img, 0, 0);
	mlx_key_hook(ctx.win, key_hook, &ctx);
	mlx_mouse_hook(ctx.win, mouse_hook, &ctx.keyboard);
	mlx_hook(ctx.win, 17, 0, close_window, &ctx);

	mlx_loop_hook(ctx.mlx, render, &ctx);
	mlx_loop(ctx.mlx);
}

