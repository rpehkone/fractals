/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:34:06 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/12 18:34:24 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		mandelbrot(float cx, float cy, int max_iter)
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

void	mandelbrot_loop(t_float_xy pos, float zoom, int max_iter, int i)
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
	while (y < i)
	{
		x = 0;
		while (x < 1280)
		{
			cx = (x - 640) * ((16.0 * zoom) / 1280) + pos.x;
			cy = (y - 360) * ((9.0 * zoom) / 720) + pos.y;
			pixel_put(x, y, 0xFF - mandelbrot(cx, cy, max_iter) * 10);
			x++;
		}
		y++;
	}
}