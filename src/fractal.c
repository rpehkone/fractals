/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/07/31 17:44:21 by rpehkone         ###   ########.fr       */
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
		mandelbrot_loop((t_args*)args, start, stop);
	}
	else if (((t_args*)args)->fractal_id == 2)
	{
		julia_loop((t_args*)args, start, stop);
	}
	else if (((t_args*)args)->fractal_id == 3)
	{
		burningship_loop((t_args*)args, start, stop);
	}
	start += 180;
	return (NULL);
}

t_args	*init_fractal(int f)
{
	static t_args	args = {.pos.x = 0, .pos.y = 0, .zoom = .3, .max_iter = 20};
	pthread_t		tid[4];
	int			i;

	if (f)
	{
		args.fractal_id = f;
		return (NULL);
	}
	i = 0;
	while (i < 4) //kuinka monta int, 5 paras?
	{
		pthread_create(&tid[i], NULL, split_screen, (void*)&args);
		usleep(100);
		i++;
	}
	return (&args);
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
}
