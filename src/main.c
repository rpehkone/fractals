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
