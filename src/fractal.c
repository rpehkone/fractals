/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/03 20:07:23 by rpehkone         ###   ########.fr       */
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
	struct sched_param params;

	params.sched_priority = sched_get_priority_max(SCHED_FIFO);
	pthread_setschedparam(pthread_self(), SCHED_FIFO, &params);
	stop += HEIGHT / THREAD_COUNT;
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
	start += HEIGHT / THREAD_COUNT;
	return (NULL);
}

t_args	*init_fractal(int f)
{
	static t_args	args = {.pos.x = 0, .pos.y = 0, .pos2.x = 0, .pos2.y = 0, .zoom2 = .3, .max_iter2 = 50, .zoom = .3, .max_iter = 40, .sync_threads = 1, .which = 0, .threads_ready = 0, .color = 5};
	int			i;
	pthread_t		tid[THREAD_COUNT];

	if (f)
	{
		args.fractal_id = f;
		return (NULL);
	}
	if (!(args.iteration = (int**)malloc(sizeof(int*) * 2)))
		exit(0);
	if (!(args.iteration[0] = (int*)malloc(sizeof(int) * (WIDTH * HEIGHT))))
		exit(0);
	if (!(args.iteration[1] = (int*)malloc(sizeof(int) * (WIDTH * HEIGHT))))
		exit(0);
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_create(&tid[i], NULL, split_screen, (void*)&args);
		usleep(10000);
		i++;
	}
	return (&args);
}

void	sync_threads(t_args *args)
{
	args->threads_ready++;
	while (args->sync_threads)
		usleep(10);
	args->out_sync++;
}

void	print_fractal(t_args *args)
{
	//eli kaikkia asetuksia pitaa doublebufferoid muuten kesken kaiken
	int	x;
	int	y;

	int old_max_iter = args->max_iter;
	y = 0;
	while (args->threads_ready < THREAD_COUNT)
		usleep(10);
	int other = args->which;
	args->which = args->which ? 0 : 1;

	args->zoom = args->zoom2;
	args->pos = args->pos2;
	args->max_iter = args->max_iter2;

	args->threads_ready = 0;
	args->sync_threads = 0;
	while (args->out_sync < THREAD_COUNT)
		usleep(10);
	args->out_sync = 0;
	args->sync_threads = 1;
	color_settings(args);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_put(x, y, select_color(args->color, old_max_iter, other, args->iteration[other][y * WIDTH + x]));
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
	if (is_mouse_down(3) || args->fractal_id == 2)
	{
		args->pos2.x -= ((float)c.x - oldc.x);
		args->pos2.y -= ((float)c.y - oldc.y);
	}
	if (is_mouse_down(2))
		args->zoom2 *= 1.1;
	if (is_mouse_down(1))
		args->zoom2 *= (1.0 / 1.1);
	if (is_mouse_down(4))
		args->zoom2 *= 1.1;
	if (is_mouse_down(5))
		args->zoom2 *= (1.0 / 1.1);
	args->max_iter2 = is_key_down(126) ? args->max_iter2 + 1 : args->max_iter2;
	args->max_iter2 = is_key_down(125) ? args->max_iter2 - 1 : args->max_iter2;
	args->max_iter2 = args->max_iter2 < 0 ? 0 : args->max_iter2;
	args->max_iter2 = args->max_iter2 > 50 ? 50 : args->max_iter2;
	oldc.x = c.x;
	oldc.y = c.y;
	//rotate_vertices(0.1, args);
	print_fractal(args);
}
