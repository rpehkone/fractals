/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:48:28 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/12 22:03:06 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

float	ft_abs(float n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

int		burningship(float cx, float cy, int max_iter)
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

void	burningship_loop(t_args *args, int i)
{
	float	cx;
	float	cy;
	int		x;
	int		y;

	y = 0;
	if (i == 720)
		y = 540;
	else if (i == 540)
		y = 360;
	else if (i == 360)
		y = 180;
	t_float_xy pos;
	pos.x = args->pos.x / (100 / args->zoom);
	pos.y = args->pos.y / (100 / args->zoom);
	while (y < i)
	{
		x = 0;
		while (x < 1280)
		{
			cx = (x - 640) * ((16.0 * args->zoom) / 1280) + pos.x / args->zoom;
			cy = (y - 360) * ((9.0 * args->zoom) / 720) + pos.y / args->zoom;
			pixel_put(x, y, 0xFF - burningship(cx, cy, args->max_iter) * 10);
			x++;
		}
		y++;
	}
}
