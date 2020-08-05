/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/05 19:03:37 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

#include <stdio.h>
t_args	*init_settings(int fractal)
{
	static t_args	args;

	if (!fractal)
		return (&args);
	if (fractal == 1)
		args.fractal = &mandelbrot;
	else if (fractal == 2)
		args.fractal = &julia;
	else if (fractal == 3)
		args.fractal = &burningship;
	args.fractal_id = fractal;
	args.max_iter = 50;
	if (fractal != 3)
	{
		args.pos.x = 0;
		args.pos.y = 0;
		args.zoom = .3;
		//args.color = 5;
		args.color = 0;
	}
	else
	{
		args.pos.x = -175;
		args.pos.y = -3;
		args.zoom = 0.0117;
		args.color = 6;
	}
	return (NULL);
}

void	*split_screen(void *args)
{
	static int	s = 0;

		mandelbrot(((t_args*)args), 0, 500);
		//((t_args*)args)->fractal(((t_args*)args), 0, 500);
	printf("xd\n");
	return (NULL);
	s++;
	if (s == THREAD_AMOUNT)
	{
		((t_args*)args)->fractal(((t_args*)args), (HEIGHT / THREAD_AMOUNT) * (s - 1),
											(HEIGHT / THREAD_AMOUNT) * s);
		s = 0;
	}
	else
		((t_args*)args)->fractal(((t_args*)args), (HEIGHT / THREAD_AMOUNT) * (s - 1),
											(HEIGHT / THREAD_AMOUNT) * s);
	return (NULL);
}

void	print_fractal(t_args *args)
{
	pthread_t	tid[THREAD_AMOUNT];
	int			i;

	i = 0;
	while (i < THREAD_AMOUNT)
	{
		pthread_create(&tid[i], NULL, split_screen, (void*)&args);
		usleep(1000);
		i++;
	}
	i = 0;
	while (i < THREAD_AMOUNT)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
}

void	handle_settings(t_args *args, t_int_xy c, t_int_xy oldc)
{
	if (is_mouse_down(3))
		args->pos.x -= ((float)c.x - oldc.x) * args->zoom;
	if (is_mouse_down(3))
		args->pos.y -= ((float)c.y - oldc.y) * args->zoom;
	if (is_key_down(126))
	   	args->max_iter += 1;
	if (is_key_down(125))
	   	args->max_iter -= 1;
	if (args->max_iter < 0)
	   	args->max_iter = 0;
	else if (args->max_iter > 50)
	   	args->max_iter = 50;
}

void	handle_zoom(t_args *args, t_int_xy c, t_int_xy oldc)
{
	if (is_mouse_down(4))
		args->pos.x -= (float)c.x - oldc.x;
	if (is_mouse_down(5))
		args->pos.y -= (float)c.y - oldc.y;
	if (is_mouse_down(1) && args->fractal_id != 2)
	{
		args->zoom = args->zoom * (1.0 / 1.1);
		if (args->zoom < 0.0000002)
			args->zoom = 0.0000002;
		else
		{
			args->pos.x += (c.x - WIDTH / 2) * (0.1 * args->zoom);
			args->pos.y += (c.y - HEIGHT / 2) * (0.1 * args->zoom);
		}
	}
	if (is_mouse_down(2) && args->fractal_id != 2)
	{
		args->zoom = args->zoom * 1.1;
		if (args->zoom > 1)
			args->zoom = 1;
		if (args->zoom < 1)
			args->pos.x += (c.x - WIDTH / 2) * (0.1 * args->zoom);
		if (args->zoom < 1)
			args->pos.y += (c.y - HEIGHT / 2) * (0.1 * args->zoom);
	}
}

void	fractal(void)
{
	static t_args	*settings = NULL;
	static t_int_xy	oldc;
	t_int_xy		cursor;

	if (is_key_down(53))
		exit(0);
	if (!settings)
		settings = init_settings(0);
	update_image();
	cursor = get_cursor();
	if (settings->fractal_id == 2)
	{
		settings->pos.x -= ((float)cursor.x - oldc.x);
		settings->pos.y -= ((float)cursor.y - oldc.y);
	}
	handle_settings(settings, cursor, oldc);
	handle_zoom(settings, cursor, oldc);
	color_settings(settings);
	oldc.x = cursor.x;
	oldc.y = cursor.y;
	print_fractal(settings);

	return ;
	static int counter = 0;
	counter++;
	if (counter > 50)
		exit(0);
}
