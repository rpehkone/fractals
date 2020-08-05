/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/05 14:16:43 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

t_settings	*init_settings(int fractal)
{
	static t_settings	settings;

	if (!fractal)
		return (&settings);
	if (fractal == 1)
		settings.fractal = &mandelbrot;
	else if (fractal == 2)
		settings.fractal = &julia;
	else if (fractal == 3)
		settings.fractal = &burningship;
	settings.fractal_id = fractal;
	settings.max_iter = 50;
	if (fractal != 3)
	{
		settings.pos.x = 0;
		settings.pos.y = 0;
		settings.zoom = .3;
		settings.color = 5;
	}
	else
	{
		settings.pos.x = -175;
		settings.pos.y = -3;
		settings.zoom = 0.0117;
		settings.color = 6;
	}
	return (NULL);
}

void	put_usage(char *arg)
{
	ft_putstr("usage: ");
	ft_putstr(arg);
	ft_putstr(" [mandelbrot | julia | burningship]\n");
}

int		main(int argc, char **argv)
{
	if (argc != 2)
		put_usage(argv[0]);
	else if (!ft_strcmp(argv[1], "mandelbrot"))
	{
		init_settings(1);
		init_window(WIDTH, HEIGHT, "mandlelbrot");
	}
	else if (!ft_strcmp(argv[1], "julia"))
	{
		init_settings(2);
		init_window(WIDTH, HEIGHT, "julia");
	}
	else if (!ft_strcmp(argv[1], "burningship"))
	{
		init_settings(3);
		init_window(WIDTH, HEIGHT, "burningship");
	}
	else
		put_usage(argv[0]);
	return (0);
}
