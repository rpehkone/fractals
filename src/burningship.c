/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:48:28 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/06 11:54:35 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		burningship_iter(PRECISION cx, PRECISION cy, int max_iter)
{
	PRECISION	zx;
	PRECISION	zy;
	PRECISION	tempx;
	int			iteration;

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

void	burningship(t_settings *settings, int start, int stop)
{
	t_position_xy	pos;
	PRECISION		cx;
	PRECISION		cy;
	int				x;
	int				y;

	y = start;
	pos.x = settings->pos.x / (100 / settings->zoom);
	pos.y = settings->pos.y / (100 / settings->zoom);
	while (y < stop)
	{
		x = 0;
		while (x < WIDTH)
		{
			cx = (x - WIDTH / 2) * ((ASPECT_WIDTH * settings->zoom) / WIDTH)
												+ pos.x / settings->zoom;
			cy = (y - HEIGHT / 2) * ((ASPECT_HEIGHT * settings->zoom) / HEIGHT)
												+ pos.y / settings->zoom;
			pixel_put(x, y, select_color(settings->color, settings->max_iter,
			settings->frame, burningship_iter(cx, cy, settings->max_iter)));
			x++;
		}
		y++;
	}
}
