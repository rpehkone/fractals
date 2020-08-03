/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/03 21:39:51 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	*split_screen(void *args)
{
	static int			start = 0;
	static int			stop = 0;
	struct sched_param	params;

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
		((t_args*)args)->color = 6;
		((t_args*)args)->pos.x = -175;
		((t_args*)args)->pos.y = -3;
		((t_args*)args)->zoom = 0.0117;
		((t_args*)args)->pos2.x = -175;
		((t_args*)args)->pos2.y = -3;
		((t_args*)args)->zoom2 = 0.0117;
		burningship((t_args*)args, start, stop);
	}
	start += HEIGHT / THREAD_COUNT;
	return (NULL);
}

void	init_args(t_args *args)
{
	args->pos.x = 0;
	args->pos.y = 0;
	args->pos2.x = 0;
	args->pos2.y = 0;
	args->zoom2 = .3;
	args->max_iter2 = 50;
	args->zoom = .3;
	args->max_iter = 50;
	args->sync_threads = 1;
	args->buffer_id = 0;
	args->threads_ready = 0;
	args->color = 5;
}

t_args	*init_fractal(int f)
{
	int				i;
	pthread_t		tid[THREAD_COUNT];
	static t_args	args;

	init_args(&args);
	if (f)
	{
		args.fractal_id = f;
		return (NULL);
	}
	if (!(args.dbuffer = (int**)malloc(sizeof(int*) * 2)))
		exit(0);
	if (!(args.dbuffer[0] = (int*)malloc(sizeof(int) * (WIDTH * HEIGHT))))
		exit(0);
	if (!(args.dbuffer[1] = (int*)malloc(sizeof(int) * (WIDTH * HEIGHT))))
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
	int	old_max_iter;
	int	not_active_id;
	int	x;
	int	y;

	old_max_iter = args->max_iter;
	while (args->threads_ready < THREAD_COUNT)
		usleep(10);
	not_active_id = args->buffer_id;
	args->buffer_id = args->buffer_id ? 0 : 1;
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
	y = 0;
	while ((x = -1) && ++y < HEIGHT)
		while (++x < WIDTH)
			pixel_put(x, y, select_color(args->color, old_max_iter,
			not_active_id, args->dbuffer[not_active_id][y * WIDTH + x]));
}

void	fractal(void)
{
	static t_args	*args = NULL;
	static t_int_xy	oldc;
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
	args->zoom2 = is_mouse_down(1) ? args->zoom2 * (1.0 / 1.1) : args->zoom2;
	args->zoom2 = is_mouse_down(2) ? args->zoom2 * 1.1 : args->zoom2;
	args->max_iter2 = is_key_down(126) ? args->max_iter2 + 1 : args->max_iter2;
	args->max_iter2 = is_key_down(125) ? args->max_iter2 - 1 : args->max_iter2;
	args->max_iter2 = args->max_iter2 < 0 ? 0 : args->max_iter2;
	args->max_iter2 = args->max_iter2 > 50 ? 50 : args->max_iter2;
	oldc.x = c.x;
	oldc.y = c.y;
	print_fractal(args);
}
