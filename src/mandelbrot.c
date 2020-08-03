/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:34:06 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/03 18:50:06 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		mandelbrot_iteration(float cx, float cy, int max_iter)
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
		tempx = zx * zx - zy * zy + cx;
		zy = 2 * zx * zy + cy;
		zx = tempx;
		iteration++;
	}
	return (iteration);
}

void	mandelbrot(t_args *a, int start, int stop)
{
	t_float_xy	pos;
	float		cx;
	float		cy;
	int			x;
	int			y;

	while (1)
	{
		y = start - 1;
		pos.x = a->pos.x / (100 / a->zoom);
		pos.y = a->pos.y / (100 / a->zoom);
		while ((x = -1) && ++y < stop)
		{
			while (++x < WIDTH)
			{
				cx = (x - WIDTH / 2) * (ASPECT_WIDTH * a->zoom)
											/ WIDTH + pos.x / a->zoom;
				cy = (y - HEIGHT / 2) * ((ASPECT_HEIGHT * a->zoom)
											/ HEIGHT) + pos.y / a->zoom;
				a->iteration[a->which][x + ((start + y) * WIDTH)] =
								mandelbrot_iteration(cx, cy, a->max_iter);
			}
		}
		sync_threads(a);
	}
}
