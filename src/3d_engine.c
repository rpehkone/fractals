/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:43:12 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/09 15:59:34 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	engine(void)
{
	t_int_xy c;
	c = get_cursor();
	printf("x = %d\n", c.x);
	printf("y = %d\n", c.y);
	if (is_mouse_down(1) && c.x > 7 && c.x < 29)
		exit(0);
	if (is_key_down(53))
		exit(0);
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
}
