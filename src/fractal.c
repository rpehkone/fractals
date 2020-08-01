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

int		set_fractal(int f)
{
	static int	fractal_id = -1;

	if (!f)
		return (fractal_id);
	if (fractal_id == -1)
		fractal_id = f;
	return (0);
}

void	what_fractal(t_args *args, int i)
{
	if (set_fractal(0) == 1)
	{
		args->pos.x /= (100 / args->zoom);
		args->pos.y /= (100 / args->zoom);
		mandelbrot_loop(args->pos, args->zoom, args->max_iter, i);
	}
	else if (set_fractal(0) == 2)
	{
		args->pos.x *= 10;
		args->pos.y *= 10;
		julia_loop(args->pos, args->zoom, args->max_iter, i);
	}
	else if (set_fractal(0) == 3)
	{
		args->pos.x /= (100 / args->zoom);
		args->pos.y /= (100 / args->zoom);
		burningship_loop(args->pos, args->zoom, args->max_iter, i);
	}
}

void	*split_screen(void *args)
{
	static int	s = 0;

	s++;
	if (s == 1)
		what_fractal((t_args*)args, 720);
	else if (s == 2)
		what_fractal((t_args*)args, 540);
	else if (s == 3)
		what_fractal((t_args*)args, 360);
	else if (s == 4)
	{
		what_fractal((t_args*)args, 180);
		s = 0;
	}
	return (NULL);
}

void	make_threads(t_args *args)
{
	pthread_t		tid[4];
	int			i;

	i = 0;
	while (i < 4)
	{
		pthread_create(&tid[i], NULL, split_screen, (void*)args);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
}

void	fractal(void)
{
	static t_args	args = {.pos.x = 0, .pos.y = 0, .zoom = .3, .max_iter = 20};

	static t_int_xy		oldc;
	t_int_xy		c;

	update_image();
	c = get_cursor();
	if (is_key_down(53))
		exit(0);
	if (is_mouse_down(1) || set_fractal(0) == 2)
	{
		args.pos.x -= ((float)c.x - oldc.x);
		args.pos.y -= ((float)c.y - oldc.y);
	}
	if (is_mouse_down(4))
		args.zoom *= 1.1;
	if (is_mouse_down(5))
		args.zoom *= (1.0 / 1.1);
	args.max_iter = is_key_down(126) ? args.max_iter + 1 : args.max_iter;
	args.max_iter = is_key_down(125) ? args.max_iter - 1 : args.max_iter;
	args.max_iter = args.max_iter < 0 ? 0 : args.max_iter;
	oldc.x = c.x;
	oldc.y = c.y;

	make_threads(&args);
}
