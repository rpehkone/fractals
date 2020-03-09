/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:05:51 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/09 20:32:56 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	mega_pixel_put(int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			pixel_put(x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	engine(void)
{
	static t_double_xyz		*nodes = NULL;
	static t_int_xy			*lines = NULL;
	static t_int_xy			color = {.x = 0x00FF00, .y = 0xFF0000};
	static int mx = 0;
	static int my = 0;
	t_int_xy c;

	if (!lines)
		lines = get_lines();
	if (!nodes)
		nodes = get_nodes();
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
	for (int i = 0; i < 12; i++)
		matrix_transform(nodes[lines[i].x], nodes[lines[i].y], color);
}
