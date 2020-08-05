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

t_settings	*init_settings(int fractal)
{
	static t_settings	settings;

	if (!fractal)
		return (&settings);
	if (fractal == 1)
		settings.fractal = &mandelbrot;
	else if (fractal == 2)
		settings.fractal = &julia;
	else if (fractal == 3)
		settings.fractal = &burningship;
	settings.fractal_id = fractal;
	settings.max_iter = 50;
	if (fractal != 3)
	{
		settings.pos.x = 0;
		settings.pos.y = 0;
		settings.zoom = .3;
		settings.color = 5;
	}
	else
	{
		settings.pos.x = -175;
		settings.pos.y = -3;
		settings.zoom = 0.0117;
		settings.color = 6;
	}
	return (NULL);
}

void	*split_screen(void *settings)
{
	
	static int	s = 0;

	s++;
	if (s == THREAD_AMOUNT)
	{
		((t_settings*)settings)->fractal(((t_settings*)settings), (HEIGHT / THREAD_AMOUNT) * (s - 1),
											(HEIGHT / THREAD_AMOUNT) * s);
		s = 0;
	}
	else
		((t_settings*)settings)->fractal(((t_settings*)settings), (HEIGHT / THREAD_AMOUNT) * (s - 1),
											(HEIGHT / THREAD_AMOUNT) * s);
	return (NULL);
}

void	print_fractal(t_settings *settings)
{
	pthread_t	tid[THREAD_AMOUNT];
	int			i;

	i = 0;
	while (i < THREAD_AMOUNT)
	{
		pthread_create(&tid[i], NULL, split_screen, (void*)settings);
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

void	handle_settings(t_settings *settings, t_int_xy c, t_int_xy oldc)
{
	if (is_mouse_down(3))
		settings->pos.x -= ((PRECISION)c.x - oldc.x) * settings->zoom;
	if (is_mouse_down(3))
		settings->pos.y -= ((PRECISION)c.y - oldc.y) * settings->zoom;
	if (is_key_down(126))
	   	settings->max_iter += 1;
	if (is_key_down(125))
	   	settings->max_iter -= 1;
	if (settings->max_iter < 0)
	   	settings->max_iter = 0;
	//else if (settings->max_iter > 50)
	 //  	settings->max_iter = 50;
}

void	handle_zoom(t_settings *settings, t_int_xy c, t_int_xy oldc)
{
	if (is_mouse_down(4))
		settings->pos.x -= (PRECISION)c.x - oldc.x;
	if (is_mouse_down(5))
		settings->pos.y -= (PRECISION)c.y - oldc.y;
	if (is_mouse_down(1) && settings->fractal_id != 2)
	{
		settings->zoom = settings->zoom * (1.0 / 1.08);
		if (settings->zoom < 0.0000002)
			;//settings->zoom = 0.0000002;
		else
		{
			settings->pos.x += (c.x - WIDTH / 2) * (0.15 * settings->zoom);
			settings->pos.y += (c.y - HEIGHT / 2) * (0.15 * settings->zoom);
		}
	}
	if (is_mouse_down(2) && settings->fractal_id != 2)
	{
		settings->zoom = settings->zoom * 1.08;
		if (settings->zoom > 1)
			settings->zoom = 1;
		if (settings->zoom < 1)
			settings->pos.x += (c.x - WIDTH / 2) * (0.15 * settings->zoom);
		if (settings->zoom < 1)
			settings->pos.y += (c.y - HEIGHT / 2) * (0.15 * settings->zoom);
	}
}

void	fractal(void)
{
	static t_settings	*settings = NULL;
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
		settings->pos.x -= ((PRECISION)cursor.x - oldc.x);
		settings->pos.y -= ((PRECISION)cursor.y - oldc.y);
	}
	handle_settings(settings, cursor, oldc);
	handle_zoom(settings, cursor, oldc);
	color_settings(settings);
	oldc.x = cursor.x;
	oldc.y = cursor.y;
	print_fractal(settings);
}
