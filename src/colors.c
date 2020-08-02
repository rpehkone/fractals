/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/01 18:31:45 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void		color_settings(t_args *args)
{
	//alussa rng vari
	static int last_down = 0;
	if (!last_down)
	{
		args->color = is_key_down(124) ? args->color + 1 : args->color;
		args->color = is_key_down(123) ? args->color - 1 : args->color;
	}
	if (args->color < 0)
		args->color = 10;
	else if (args->color > 10)
		args->color = 0;
	last_down = is_key_down(124) || is_key_down(123) ? 1 : 0;
}

int		select_color(int color, int max, int other, int iteration)
{
	if (color == 0)
		return (iteration < max ? 0xFFFFFF : 0);
	else if (color == 1)
	{
		if (iteration == max)
			return (0xFFFFFF);
		float asd = ((float)(max - iteration) / max);
		int a = 0xFF * asd;
		return ((a * 0x10000) + (a * 0x100) + 0xFF);
	}
	else if (color == 2)
	{
		if (iteration == max)
			return (0xFFFFFF);
		else if (iteration < max / 2)
		{
			max /= 2;
			float asd = ((float)(max - iteration) / max);
			int a = 0xFF - 0xFF * asd;
			return ((a * 0x10000));
		}
		else
		{
			iteration /= 2;
			max /= 2;
			float asd = (float)iteration / max;
			int a = 0xFF * asd;
			return ((0xFF0000) + (a * 0x100) + 0);
		}
	}
	else if (color == 3)
	{
		if (iteration == max)
			return (0xFFFFFF);
		else if (iteration % 2)
			return (0xFF7777);
		else
			return (0xFFCCCC);
	}
	else if (color == 4)
	{
		if (iteration == max)
			return (0xFF0000);
		return (-216380416);
	}
	else if (color == 5)
	{
		static int other2 = 0;
		static int asd = 0;

		if (other2 != other) 
		{
			other2 = other;
			asd++;
		}
		if (asd > 12)
			asd = 0;
		if (iteration == max)
			return (0xFFFFFF);
		iteration += asd / 4;
		if (!(iteration % 4))
			return (0xFF0000);
		else if (!((iteration + 1) % 4))
			return (0xFF00);
		else if (!((iteration + 2) % 4))
			return (0xFF);
		return (0xFF00FF);
	}
	else if (color == 6)
	{
		static int other2 = 0;
		static int asd = 0;

		if (other2 != other) 
		{
			other2 = other;
			asd++;
		}
		if (asd > 36)
			asd = 0;
		int xd = asd / 12;
		if (!xd)
			xd++;
		if (iteration == max)
			return (0xFFFFFF);
		else if (iteration < max / xd)
		{
			max /= xd;
			float asd = ((float)(max - iteration) / max);
			int a = 0xFF - 0xFF * asd;
			return ((a * 0x10000));
		}
		else
		{
			iteration /= xd;
			max /= xd;
			float asd = (float)iteration / max;
			int a = 0xFF * asd;
			return ((0xFF0000) + (a * 0x100) + 0);
		}
	}
	int asd = 0xFF - iteration;
	if (iteration < max / 2)
		return (asd * 0x100 / 2) + asd / 2;
	else
		return (0xFFFFFF);
}
