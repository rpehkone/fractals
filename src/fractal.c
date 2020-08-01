/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/01 11:21:43 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	*split_screen(void *args)
{
	static int	start = 0;
	static int	stop = 0;

	stop += 180;
	if (((t_args*)args)->fractal_id == 1)
	{
		mandelbrot((t_args*)args, start, stop);
	}
	else if (((t_args*)args)->fractal_id == 2)
	{
		julia((t_args*)args, start, stop);
	}
	else if (((t_args*)args)->fractal_id == 3)
	{
		burningship((t_args*)args, start, stop);
	}
	start += 180;
	return (NULL);
}

t_args	*init_fractal(int f)
{
	static t_args	args = {.pos.x = 0, .pos.y = 0, .zoom = .3, .max_iter = 20};
	int			i;
	pthread_t		tid[4];

	if (f)
	{
		args.fractal_id = f;
		return (NULL);
	}
	if (!(args.iteration = (int*)malloc(sizeof(int) * (1280 * 720))))
		exit(0);
	i = 0;
	while (i < 4) //kuinka monta int, 5 paras?
	{
		pthread_create(&tid[i], NULL, split_screen, (void*)&args);
		usleep(100);
		i++;
	}
	return (&args);
}

void	print_fractal(t_args *args)
{
	int	x;
	int	y;

	y = 0;
	while (y < 720)
	{
		x = 0;
		while (x < 1280)
		{
			if (args->iteration[(y * 1280 + x)] < args->max_iter)
				pixel_put(x, y, 0xFF);
			else
				pixel_put(x, y, 0);
			x++;
		}
		y++;
	}
}

void	fractal(void)
{
	static t_args	*args = NULL;
	static t_int_xy		oldc;
	t_int_xy		c;

	if (is_key_down(53))
		exit(0);
	if (!args)
		args = init_fractal(0);
	update_image();
	c = get_cursor();
	if (is_mouse_down(1) || args->fractal_id == 2)
	{
		args->pos.x -= ((float)c.x - oldc.x);
		args->pos.y -= ((float)c.y - oldc.y);
	}
	if (is_mouse_down(4))
		args->zoom *= 1.1;
	if (is_mouse_down(5))
		args->zoom *= (1.0 / 1.1);
	args->max_iter = is_key_down(126) ? args->max_iter + 1 : args->max_iter;
	args->max_iter = is_key_down(125) ? args->max_iter - 1 : args->max_iter;
	args->max_iter = args->max_iter < 0 ? 0 : args->max_iter;
	oldc.x = c.x;
	oldc.y = c.y;
	print_fractal(args);
}
