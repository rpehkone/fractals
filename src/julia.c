/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/01 12:08:26 by rpehkone         ###   ########.fr       */
/* ************************************************************************** */

#include "fractal.h"

int		julia_iteration(float cx, float cy, int max_iter, t_float_xy pos)
{
	float	zx;
	float	zy;
	float	tempx;
	int		iteration;

	zx = 0;
	zy = 0;
	iteration = 0;
	zx = cx;
	zy = cy;
	cx = (3.0 / 1280) * (pos.x - 1280 / 2);
	cy = (2.0 / 720) * (pos.y - 720 / 2);
	while ((zx * zx + zy * zy < 4) && (iteration < max_iter))
	{
		tempx = zx * zx - zy * zy + cx;
		zy = 2 * zx * zy + cy;
		zx = tempx;
		iteration++;
	}
	return (iteration);
}
//add auto rotate
void	julia(t_args *args, int start, int stop)
{
	float	cx;
	float	cy;
	int		x;
	int		y;
	t_float_xy	pos;

	while (1)
	{
		y = start;
		pos.y = args->pos.x * 1;
		pos.x = args->pos.y * -1;
		while (y < stop)
		{
			x = 0;
			while (x < 1280)
			{
				cx = (x - 640) * ((16.0 * args->zoom) / 1280);
				cy = (y - 360) * ((9.0 * args->zoom) / 720);
				args->iteration[args->which][x + ((start + y) * 1280)] = julia_iteration(cx, cy, args->max_iter, pos);
				x++;
			}
			y++;
		}
		args->threads_ready++;
		while (args->sync_threads)
			usleep(10);
	}
}
