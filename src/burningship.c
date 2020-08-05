/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:48:28 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/05 18:41:56 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		burningship_iteration(PRECISION cx, PRECISION cy, int max_iter)
{
	PRECISION	zx;
	PRECISION	zy;
	PRECISION	tempx;
	int		iteration;

	zx = 0;
	zy = 0;
	iteration = 0;
	while ((zx * zx + zy * zy < 4) && (iteration < max_iter))
	{
		zx = zx < 0 ? zx * -1 : zx;
		zy = zy < 0 ? zy * -1 : zy;
		tempx = zx * zx - zy * zy + cx;
		zy = 2 * zx * zy + cy;
		zx = tempx;
		iteration++;
	}
	return (iteration);
}

void	burningship(t_args *args, int start, int stop)
{
	t_position_xy	pos;
	PRECISION		cx;
	PRECISION		cy;
	int			x;
	int			y;

	y = start - 1;
	pos.x = args->pos.x / (100 / args->zoom);
	pos.y = args->pos.y / (100 / args->zoom);
	while ((x = -1) && ++y < stop)
		while (++x < WIDTH)
		{
			cx = (x - WIDTH / 2) * ((ASPECT_WIDTH * args->zoom) / WIDTH)
												+ pos.x / args->zoom;
			cy = (y - HEIGHT / 2) * ((ASPECT_HEIGHT * args->zoom) / HEIGHT)
												+ pos.y / args->zoom;
			pixel_put(x, y, select_color(args->color, args->max_iter, args->frame, burningship_iteration(cx, cy, args->max_iter)));
		}
}
