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

float	ft_abs(float n)
{
	return (n < 0 ? n * -1 : n);
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
	t_float_xy	pos;
	float		cx;
	float		cy;
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
			//args->dbuffer[args->buffer_id][x + ((start + y) * WIDTH)] =
			//				burningship_iteration(cx, cy, args->max_iter);
		}
}
