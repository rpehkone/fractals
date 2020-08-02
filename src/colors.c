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

/*
int		set_gradient_color(int x, int y)
{
	double	red;
	double	grn;
	double	blu;
	int		i;

	i = 0;
	while (i < 310)
	{
		red = sin(0.02 * i + 0) * 127 + 128;
		grn = sin(0.02 * i + 2) * 127 + 128;
		blu = sin(0.02 * i + 4) * 127 + 128;
		if (i == x && y < 450 && y > 30)
			return ((int)red * 65536 + (int)grn * 256 + (int)blu);
		i++;
	}
	return (0);
}
*/
int		get_color_7(float fade, int max, int other, int iteration)
{
	(void)fade;
	(void)other;
	int asd = 0xFF - iteration;
	if (iteration < max / 2)
		return (asd * 0x100 / 2) + asd / 2;
	else
		return (0xFFFFFF);
}

int		get_color_6(float fade, int max, int other, int iteration)
{
	/*
		red = 120 + rand(120);
		yellow = 120 + rand(120);
		yellow = 120 + rand(120);
		sleep(rand(100))
	*/
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
		int a = 0xFF - 0xFF * (fade / 1.25);
		return ((a * 0x10000));
	}
	return ((0xFF0000) + ((0xFF * (fade / 2)) * 0x100) + 0);
}

int		get_color_5(float fade, int max, int other, int iteration)
{
	static int other2 = 0;
	static int asd = 0;

	(void)fade;
	(void)other;
	if (other2 != other)
	{
		other2 = other;
		asd++;
	}
	if (asd > 16)
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

int		select_color(int color, int max, int other, int iteration)
{
	float fade = ((float)(max - iteration) / max);

	if (color == 0)
		return (iteration < max ? 0xFFFFFF : 0);
	else if (color == 1)
		return (iteration == max ? 0xFFFFFF :
		((int)(0xFF * fade) * 0x10000) + ((int)(0xFF * fade) * 0x100) + 0xFF);
	else if (color == 2 && iteration == max)
		return (0xFFFFFF);
	else if (color == 2)//muuta taa musta valko musta // tai musta vaaleanpunanen musta
		return (iteration < (max / 2) ? ((0xFF - (int)(0xFF * (fade / 1.25))) * 0x10000) :
				 0xFF0000 + (int)(0xFF * (fade / 2)) * 0x100);
	else if (color == 3 && iteration == max)
		return (0xFFFFFF);
	else if (color == 3)
		return (iteration % 2 ? 0xFF7777 : 0xFFCCCC);
	else if (color == 4)
		return  (iteration == max ? 0xFF0000 : -216380416);
	else if (color == 5)
		return(get_color_5(fade, max, other, iteration));
	else if (color == 6)
		return(get_color_6(fade, max, other, iteration));
	return(get_color_7(fade, max, other, iteration));
}

void		color_settings(t_args *args)
{
	static int last_down = 0;

	//at start rng vari
	if (!last_down)
	{
		args->color = is_key_down(124) ? args->color + 1 : args->color;
		args->color = is_key_down(123) ? args->color - 1 : args->color;
	}
	if (args->color < 0)
		args->color = 7;
	else if (args->color > 7)
		args->color = 0;
	last_down = is_key_down(124) || is_key_down(123) ? 1 : 0;
}
