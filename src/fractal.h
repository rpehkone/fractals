/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:02:30 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/01 11:19:44 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# include "mlx_io.h"
# include <pthread.h>

#include <stdio.h>
//poista taa struct?
typedef struct	s_float_xy {
	float		x;
	float		y;
}				t_float_xy;

typedef struct	s_args {
	t_float_xy	pos;
	float		zoom;
	int			max_iter;
	int			fractal_id;
	int			*iteration;
}				t_args;

void			mandelbrot(t_args *args, int start, int stop);
void			julia(t_args *args, int start, int stop);
void			burningship(t_args *args, int start, int stop);
t_args				*init_fractal(int i);

#endif
