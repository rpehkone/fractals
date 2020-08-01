/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/01 11:40:41 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	put_usage(char *arg)
{
	ft_putstr("usage: ");
	ft_putstr(arg);
	ft_putstr(" [mandelbrot | julia | burningship]\n");
}

int		main(int argc, char **argv)
{
	int	width;
	int	height;

	width = 1280;
	height = 720;
	// vai argc < 2
	if (argc != 2)
		put_usage(argv[0]);
	else if (!ft_strcmp(argv[1], "mandelbrot"))
	{
		init_fractal(1);
		init_window(width, height, "mandlelbrot");
	}
	else if (!ft_strcmp(argv[1], "julia"))
	{
		init_fractal(2);
		init_window(width, height, "julia");
	}
	else if (!ft_strcmp(argv[1], "burningship"))
	{
		init_fractal(3);
		init_window(width, height, "burningship");
	}
	else
		put_usage(argv[0]);
	return (0);
}
