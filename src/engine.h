/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_engine.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:02:30 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/09 18:37:50 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "fdf.h"
#include <stdio.h>
#include <math.h>

typedef struct	s_double_xyz {
	double		x;
	double		y;
	double		z;
}				t_double_xyz;

void	engine(void);
void	print_line(t_double_xyz start, t_double_xyz stop, t_int_xy color);
void			rotate_x(float angle, t_double_xyz *nodes, int amount);
void			rotate_y(float angle, t_double_xyz *nodes, int amount);
void			rotate_z(float angle, t_double_xyz *nodes, int amount);
t_double_xyz	*get_nodes(void);
t_int_xy		*get_lines(void);
