/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/04 17:49:04 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	sync_threads(t_args *args)
{
	args->threads_ready++;
	while (args->sync_threads)
		usleep(1);
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
		usleep(1);
	not_active_id = args->buffer_id;
	args->buffer_id = args->buffer_id ? 0 : 1;
	args->zoom = args->zoom2;
	args->pos = args->pos2;
	args->max_iter = args->max_iter2;
	args->threads_ready = 0;
	args->sync_threads = 0;
	while (args->out_sync < THREAD_COUNT)
		usleep(1);
	args->sync_threads = 1;
	args->out_sync = 0;
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
	if (args->fractal_id == 2)
	{
		args->pos2.x -= ((float)c.x - oldc.x);
		args->pos2.y -= ((float)c.y - oldc.y);
	}
	else if (is_mouse_down(3))
	{
		args->pos2.x -= ((float)c.x - oldc.x) * args->zoom2;
		args->pos2.y -= ((float)c.y - oldc.y) * args->zoom2;
	}
	if (is_mouse_down(1) && args->fractal_id != 2)
	{
		args->pos2.x += (c.x - WIDTH / 2) * (0.1 * args->zoom2);
		args->pos2.y += (c.y - HEIGHT / 2) * (0.1 * args->zoom2);
	}
	if (is_mouse_down(2) && args->fractal_id != 2)
	{
		args->pos2.x += (c.x - WIDTH / 2) * (0.1 * args->zoom2);
		args->pos2.y += (c.y - HEIGHT / 2) * (0.1 * args->zoom2);
	}
	args->zoom2 = is_mouse_down(1) ? args->zoom2 * (1.0 / 1.1) : args->zoom2;
	args->zoom2 = is_mouse_down(2) ? args->zoom2 * 1.1 : args->zoom2;
	if (args->zoom2 > 1)
		args->zoom2 = 1;
	else if (args->zoom2 < 0.0000001)
		args->zoom2 = 0.0000001;
	args->max_iter2 = is_key_down(126) ? args->max_iter2 + 1 : args->max_iter2;
	args->max_iter2 = is_key_down(125) ? args->max_iter2 - 1 : args->max_iter2;
	args->max_iter2 = args->max_iter2 < 0 ? 0 : args->max_iter2;
	args->max_iter2 = args->max_iter2 > 50 ? 50 : args->max_iter2;
	oldc.x = c.x;
	oldc.y = c.y;
	print_fractal(args);
}
