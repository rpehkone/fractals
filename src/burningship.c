/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:48:28 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/01 15:57:01 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

float	ft_abs(float n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

int		burningship_iteration(float cx, float cy, int max_iter)
{
	float	zx;
	float	zy;
	float	tempx;
	int		iteration;

	zx = 0;
	zy = 0;
	iteration = 0;
	while ((zx * zx + zy * zy < 4) && (iteration < max_iter))
	{
		zx = ft_abs(zx);
		zy = ft_abs(zy);
		tempx = zx * zx - zy * zy + cx;
		zy = 2 * zx * zy + cy;
		zx = tempx;
		iteration++;
	}
	return (iteration);
}

void	burningship(t_args *args, int start, int stop)
{
	float	cx;
	float	cy;
	int		x;
	int		y;
	t_float_xy	pos;

	//alottaa siita laivasta
	while (1)
	{
		usleep(100);
		y = start;
		pos.x = args->pos.x / (100 / args->zoom);
		pos.y = args->pos.y / (100 / args->zoom);
		while (y < stop)
		{
			x = 0;
			while (x < 1280)
			{
				cx = (x - 640) * ((16.0 * args->zoom) / 1280) + pos.x / args->zoom;
				cy = (y - 360) * ((9.0 * args->zoom) / 720) + pos.y / args->zoom;
				args->iteration[args->which][x + ((start + y) * 1280)] = burningship_iteration(cx, cy, args->max_iter);
				x++;
			}
			y++;
		}
		args->threads_ready++;
		while (args->sync_threads)
			usleep(10);
	}
}
