/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/09 18:11:52 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	draw(t_double_xyz *nodes, t_int_xy *lines, t_int_xy color)
{
	for (int i = 0; i <= 7; i++)
	{
		nodes[i].x += 400;
		nodes[i].y += 400;
		nodes[i].z += 700;
	}
	for (int i = 0; i < 12; i++)
	{
		print_line(nodes[lines[i].x], nodes[lines[i].y], color);
	}
	for (int i = 0; i <= 7; i++)
	{
		nodes[i].x -= 400;
		nodes[i].y -= 400;
		nodes[i].z -= 700;
	}
}

void	engine(void)
{
	static t_double_xyz		*nodes = NULL;
	static t_int_xy			*lines = NULL;
	static t_int_xy			color = {.x = 0x00FF00, .y = 0xFF0000};

	if (!lines)
	{
		lines = (t_int_xy*)malloc(sizeof(t_int_xy) * 12);
		lines[0].x = 0;
		lines[0].y = 1;

		lines[4].x = 0;
		lines[4].y = 2;

		lines[5].x = 0;
		lines[5].y = 4;

		lines[1].x = 1;
		lines[1].y = 3;

		lines[2].x = 1;
		lines[2].y = 5;

		lines[3].x = 2;
		lines[3].y = 3;

		lines[6].x = 2;
		lines[6].y = 6;

		lines[7].x = 3;
		lines[7].y = 7;

		lines[8].x = 4;
		lines[8].y = 5;

		lines[9].x = 4;
		lines[9].y = 6;

		lines[10].x = 5;
		lines[10].y = 7;

		lines[11].x = 6;
		lines[11].y = 7;

	}
	if (!nodes)
	{
		nodes = (t_double_xyz*)malloc(sizeof(t_double_xyz) * 8);
		nodes[0].x = -100;
		nodes[0].y = -100;
		nodes[0].z = -100;

		nodes[1].x = -100;
		nodes[1].y = -100;
		nodes[1].z = 100;

		nodes[2].x = -100;
		nodes[2].y = 100;
		nodes[2].z = -100;

		nodes[3].x = -100;
		nodes[3].y = 100;
		nodes[3].z = 100;

		nodes[4].x = 100;
		nodes[4].y = -100;
		nodes[4].z = -100;

		nodes[5].x = 100;
		nodes[5].y = -100;
		nodes[5].z = 100;

		nodes[6].x = 100;
		nodes[6].y = 100;
		nodes[6].z = -100;

		nodes[7].x = 100;
		nodes[7].y = 100;
		nodes[7].z = 100;
	}
	static int mx = 0;
	static int my = 0;
	t_int_xy c;

	c = get_cursor();
	if (is_mouse_down(1) && c.x > 7 && c.x < 29)
		exit(0);
	if (is_key_down(53))
		exit(0);
	if (is_mouse_down(1))
	{
		rotate_y(0.01 * (mx - c.x), nodes, 8);
		rotate_x(-1 * 0.01 * (my - c.y), nodes, 8);
	}
	mx = c.x;
	my = c.y;
	draw(nodes, lines, color);
	/*
	pixel_put(0, 0, 0xFF0000);
	pixel_put(0, 1, 0xFF0000);
	pixel_put(0, 2, 0xFF0000);
	pixel_put(0, 3, 0xFF0000);
	pixel_put(1, 0, 0xFF0000);
	pixel_put(1, 1, 0xFF0000);
	pixel_put(1, 2, 0xFF0000);
	pixel_put(1, 3, 0xFF0000);
	pixel_put(2, 0, 0xFF0000);
	pixel_put(2, 1, 0xFF0000);
	pixel_put(2, 2, 0xFF0000);
	pixel_put(2, 3, 0xFF0000);
	pixel_put(3, 0, 0xFF0000);
	pixel_put(3, 1, 0xFF0000);
	pixel_put(3, 2, 0xFF0000);
	pixel_put(3, 3, 0xFF0000);
	*/
}
