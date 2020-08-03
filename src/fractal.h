/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:02:30 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/03 18:58:40 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# include "mlx_io.h"
# include <pthread.h>
# include <math.h>
# define THREAD_COUNT 5
# define WIDTH 960
# define HEIGHT 550
# define ASPECT_WIDTH 16.0
# define ASPECT_HEIGHT 9.0

#include <stdio.h>

typedef struct	s_float_xy {
	float		x;
	float		y;
}				t_float_xy;

typedef struct	s_args {
	t_float_xy	pos;
	t_float_xy	pos2;
	float		zoom;
	float		zoom2;
	int			max_iter;
	int			max_iter2;

	int			fractal_id;
	int			**iteration;
	int			threads_ready;
	int			sync_threads;
	int			out_sync;
	int			which;
	int			color;
}				t_args;

void			mandelbrot(t_args *args, int start, int stop);
void			julia(t_args *args, int start, int stop);
void			burningship(t_args *args, int start, int stop);
t_args			*init_fractal(int i);
void			color_settings(t_args *args);
int				select_color(int color, int max, int other, int iteration);
void			sync_threads(t_args *args);
#endif
