/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/12 18:34:48 by rpehkone         ###   ########.fr       */ /*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		julia(float cx, float cy, int max_iter, t_float_xy pos)
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

void	julia_loop(t_args *args, int start, int stop)
{
	float	cx;
	float	cy;
	int		x;
	int		y;
	t_float_xy	pos;

	while (1)
	{
		y = start;
		pos.x = args->pos.x * 10;
		pos.y = args->pos.y * 10;
		while (y < stop)
		{
			x = 0;
			while (x < 1280)
			{
				cx = (x - 640) * ((16.0 * args->zoom) / 1280);
				cy = (y - 360) * ((9.0 * args->zoom) / 720);
				pixel_put(x, y, 0xFF - julia(cx, cy, args->max_iter, pos) * 10);
				x++;
			}
			y++;
		}
	}
}
