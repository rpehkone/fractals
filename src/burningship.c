/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:48:28 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/03 18:54:11 by rpehkone         ###   ########.fr       */
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
	float	cx;
	float	cy;
	int		x;
	int		y;
	t_float_xy	pos;

	//color 6 animoitu kaikkiin?
	args->color = 2;
	args->pos.x = -175;
	args->pos.y = -3;
	args->zoom = 0.0117;
	args->pos2.x = -175;
	args->pos2.y = -3;
	args->zoom2 = 0.0117;
	while (1)
	{
		usleep(100);
		y = start;
		pos.x = args->pos.x / (100 / args->zoom);
		pos.y = args->pos.y / (100 / args->zoom);
		while (y < stop)
		{
			x = 0;
			while (x < WIDTH)
			{
				cx = (x - WIDTH / 2) * ((ASPECT_WIDTH * args->zoom) / WIDTH) + pos.x / args->zoom;
				cy = (y - HEIGHT / 2) * ((ASPECT_HEIGHT * args->zoom) / HEIGHT) + pos.y / args->zoom;
				args->iteration[args->which][x + ((start + y) * WIDTH)] = burningship_iteration(cx, cy, args->max_iter);
				x++;
			}
			y++;
		}
		sync_threads(args);
	}
}
