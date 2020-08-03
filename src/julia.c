/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:40:28 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/03 18:42:25 by rpehkone         ###   ########.fr       */
/*                                                                            */
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
	cx = (3.0 / WIDTH) * (pos.x - WIDTH / 2);
	cy = (2.0 / HEIGHT) * (pos.y - HEIGHT / 2);
	while ((zx * zx + zy * zy < 4) && (iteration < max_iter))
	{
		tempx = zx * zx - zy * zy + cx;
		zy = 2 * zx * zy + cy;
		zx = tempx;
		iteration++;
	}
	return (iteration);
}

void	julia(t_args *args, int start, int stop)
{
	t_float_xy	pos;
	float		cx;
	float		cy;
	int			x;
	int			y;

	while (1)
	{
		y = start;
		pos.x = args->pos.x + WIDTH;
		pos.y = args->pos.y + HEIGHT;
		while (!(x = 0) && y < stop)
		{
			while (x < WIDTH)
			{
				cx = (x - WIDTH / 2) * ((ASPECT_WIDTH * args->zoom) / WIDTH);
				cy = (y - HEIGHT / 2) * ((ASPECT_HEIGHT * args->zoom) / HEIGHT);
				args->iteration[args->which][x + ((start + y) * WIDTH)] =
								julia_iteration(cx, cy, args->max_iter, pos);
				x++;
			}
			y++;
		}
		sync_threads(args);
	}
}
