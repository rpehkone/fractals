/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/03 16:01:21 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"
/*
void	rotate_vertices(float angle, t_args *args)
{
	static t_int_xy asd = {.x = 10, .y = 10};
	float	sin_angle;
	float	cos_angle;
	float	a;
	float	b;

	sin_angle = sin(angle);
	cos_angle = cos(angle);

	args->pos.y -= asd.y;
	args->pos.x -= asd.x;
	a = asd.x;
	b = asd.y;
	asd.y = (a * cos_angle - b * sin_angle);
	asd.x = (b * cos_angle + a * sin_angle);
	args->pos.y += asd.y;
	args->pos.x += asd.x;
}
*/
void	*split_screen(void *args)
{
	static int	start = 0;
	static int	stop = 0;

	stop += 180;
	if (((t_args*)args)->fractal_id == 1)
	{
		mandelbrot((t_args*)args, start, stop);
	}
	else if (((t_args*)args)->fractal_id == 2)
	{
		julia((t_args*)args, start, stop);
	}
	else if (((t_args*)args)->fractal_id == 3)
	{
		burningship((t_args*)args, start, stop);
	}
	start += 180;
	return (NULL);
}

t_args	*init_fractal(int f)
{
	static t_args	args = {.pos.x = 0, .pos.y = 0, .pos2.x = 0, .pos2.y = 0, .zoom2 = .3, .max_iter2 = 50, .zoom = .3, .max_iter = 50, .sync_threads = 1, .which = 1, .threads_ready = 0, .color = 0};
	int			i;
	pthread_t		tid[4];

	if (f)
	{
		args.fractal_id = f;
		return (NULL);
	}
	if (!(args.iteration = (int**)malloc(sizeof(int*) * 2)))
		exit(0);
	if (!(args.iteration[0] = (int*)malloc(sizeof(int) * (1280 * 720))))
		exit(0);
	if (!(args.iteration[1] = (int*)malloc(sizeof(int) * (1280 * 720))))
		exit(0);
	i = 0;
	while (i < 4) //kuinka monta int, 5 paras?
	{
		pthread_create(&tid[i], NULL, split_screen, (void*)&args);
		usleep(100);
		i++;
	}
	return (&args);
}

void	print_fractal(t_args *args)
{
	//eli kaikkia asetuksia pitaa doublebufferoid muuten kesken kaiken
	int	x;
	int	y;

	int old_max_iter = args->max_iter;
	y = 0;
	while (args->threads_ready < 4)
		usleep(10);
	args->threads_ready = 0;
	int other = args->which;
	args->which = args->which ? 0 : 1;

	args->zoom = args->zoom2;
	args->pos = args->pos2;
	args->max_iter = args->max_iter2;

	usleep(100);
	args->sync_threads = 0;
	usleep(100);
	args->sync_threads = 1;
	color_settings(args);
	while (y < 720)
	{
		x = 0;
		while (x < 1280)
		{
			pixel_put(x, y, select_color(args->color, old_max_iter, other, args->iteration[other][y * 1280 + x]));
			x++;
		}
		y++;
	}
}

void	fractal(void)
{
//jos on huono fps laskee resoluutiota
//tai tee feikki resoluutio isompi ikkuna
	static t_args	*args = NULL;
	static t_int_xy		oldc;
	t_int_xy		c;

	if (is_key_down(53))
		exit(0);
	if (!args)
		args = init_fractal(0);
	update_image();
	c = get_cursor();
	if (is_mouse_down(1) || args->fractal_id == 2)
	{
		args->pos2.x -= ((float)c.x - oldc.x);
		args->pos2.y -= ((float)c.y - oldc.y);
	}
	if (is_mouse_down(4))
		args->zoom2 *= 1.1;
	if (is_mouse_down(5))
		args->zoom2 *= (1.0 / 1.1);
	args->max_iter2 = is_key_down(126) ? args->max_iter2 + 1 : args->max_iter2;
	args->max_iter2 = is_key_down(125) ? args->max_iter2 - 1 : args->max_iter2;
	args->max_iter2 = args->max_iter < 0 ? 0 : args->max_iter2;
	oldc.x = c.x;
	oldc.y = c.y;
	//rotate_vertices(0.1, args);
	print_fractal(args);
}
