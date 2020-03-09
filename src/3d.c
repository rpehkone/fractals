/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/09 20:32:21 by rpehkone         ###   ########.fr       */
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

void	matrix_transform(t_double_xyz start, t_double_xyz stop, t_int_xy color)
{
	static int	obj_distance = 700;
	//static int	focal_len = 1025;

	if (is_mouse_down(4))
		obj_distance -= 10;
	if (is_mouse_down(5))
		obj_distance += 10;
	start.z += obj_distance;
	stop.z += obj_distance;
	start.x += 500;
	start.y += 500;
	stop.x += 500;
	stop.y += 500;
	/*start.x /= (start.z / focal_len);
	start.y /= (start.z / focal_len);
	stop.x /= (stop.z / focal_len);
	stop.y /= (stop.z / focal_len);
	*///if (/*perspective is on &&*/  start.z < 0 || stop.z < 0)
	printf("%f\n", start.x);
		print_line(start, stop, color);
}

void	engine(void)
{
	static t_double_xyz		*nodes = NULL;
	static t_int_xy			*lines = NULL;
	static t_int_xy			color = {.x = 0x00FF00, .y = 0xFF0000};
	static int old_mouse_x = 0;
	static int old_mouse_y = 0;
	t_int_xy c;

	if (!lines)
	{
		lines = get_lines();
		nodes = get_nodes();
	}
	//read_file(&nodes, &lines, &v_amount, &l_amount);
	c = get_cursor();
	if (is_mouse_down(1) && c.x > 7 && c.x < 29)
		exit(0);
	if (is_key_down(53))
		exit(0);
	if (is_mouse_down(1))
	{
		rotate_y(0.01 * (old_mouse_x - c.x), nodes, 8);
		rotate_x(-1 * 0.01 * (old_mouse_y - c.y), nodes, 8);
	}
	old_mouse_x = c.x;
	old_mouse_y = c.y;
	for (int i = 0; i < 12; i++)
		matrix_transform(nodes[lines[i].x], nodes[lines[i].y], color);
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
