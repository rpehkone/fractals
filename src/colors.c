/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/04 16:18:30 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		get_color_6(int max, int other, int iteration)
{
	static int other2 = 0;
	static int wait_i = 1;
	static int wait_time = 0;
	static float fire_amount = 0;

	if (other2 != other)
	{
		other2 = other;
		wait_i++;
	}
	if (wait_i > wait_time)
	{
		wait_i = 0;
		wait_time = rand() % 10;
		fire_amount = (float)(rand() % 100) / 100 + 1;
		int j = rand() % 3;
		if (j < 3)
			fire_amount += 1.5;
	}
	if (iteration == max)
		return (0xFFFFFF);
	else if (iteration < max / fire_amount)
	{
		max /= fire_amount;
		float asd = (float)(max - iteration) / max;
		int a = 0xFF - 0xFF * asd;
		return ((a * 0x10000));
	}
	iteration /= fire_amount;
	max /= fire_amount;
	float asd = (float)iteration / max;
	int a = 0xFF * asd;
	return ((0xFF0000) + (a * 0x100) + 0);
}

int		get_color_5(float fade, int other, int i)
{
	static int other2 = 0;
	static int asd = 0;
	double	red;
	double	grn;
	double	blu;

	if (other2 != other)
	{
		other2 = other;
		asd += 5;
	}
	if (asd > 310)
		asd = 0;

	int x = 310 * fade;
	x += asd;
	if (x > 310)
		x -= 310;
	i = 0;
	while (i < 310 && i != x)
		i++;
	red = sin(0.02 * i + 0) * 127 + 128;
	grn = sin(0.02 * i + 2) * 127 + 128;
	blu = sin(0.02 * i + 4) * 127 + 128;
	return ((int)red * 65536 + (int)grn * 256 + (int)blu);
}

int		select_color(int color, int max, int other, int iteration)
{
	float fade = ((float)(max - iteration) / max);

	if (color == 0)
		return (iteration < max ? 0xFFFFFF : 0);
	else if (color == 1)
		return (iteration == max ? 0xFFFFFF :
		((int)(0xFF * fade) * 0x10000) + ((int)(0xFF * fade) * 0x100) + 0xFF);
	else if (color == 2)
	{
		float fade_inv = 1 - fade;
		fade_inv *= 2;

		float test = fade;
		test *= 2;
		return (iteration < (max / 2) ? ((int)(0xFF * fade_inv) * 0x10000) + ((int)(0xFF * fade_inv) * 0x100) + (int)(0xFF * fade_inv) :
			((int)(0xFF * test) * 0x10000) + ((int)(0xFF * test) * 0x100) + (int)(0xFF * test));
	}
	else if (color == 3 && iteration == max)
		return (0xFFFFFF);
	else if (color == 3)
		return (iteration % 2 ? 0xFF7777 : 0xFFCCCC);
	else if (color == 4)
		return  (iteration == max ? 0xFF0000 : -216380416);
	else if (color == 5)
		return(get_color_5(fade, other, 0));
	return(get_color_6(max, other, iteration));
}

void		color_settings(t_args *args)
{
	static int last_down = 0;

	if (!last_down)
	{
		args->color = is_key_down(124) ? args->color + 1 : args->color;
		args->color = is_key_down(123) ? args->color - 1 : args->color;
	}
	if (args->color < 0)
		args->color = 6;
	else if (args->color > 6)
		args->color = 0;
	last_down = is_key_down(124) || is_key_down(123) ? 1 : 0;
}
