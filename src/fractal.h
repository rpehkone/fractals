/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:02:30 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/05 18:46:11 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# include "mlx_io.h"
# include <pthread.h>
# include <math.h>
# define THREAD_AMOUNT 1
# define WIDTH 960
# define HEIGHT 550
//# define WIDTH 1920
//# define HEIGHT 1080
# define ASPECT_WIDTH 16.0
# define ASPECT_HEIGHT 9.0

typedef struct	s_float_xy {
	float		x;
	float		y;
}				t_float_xy;

typedef struct	s_args {
	t_float_xy	pos;
	float		zoom;
	int			max_iter;
	int			color;
	int			fractal_id;
	void		(*fractal)(struct s_args*, int, int);
}				t_args;

void			mandelbrot(t_args *args, int start, int stop);
void			julia(t_args *args, int start, int stop);
void			burningship(t_args *args, int start, int stop);
t_args			*init_settings(int i);
void			color_settings(t_args *args);
int				select_color(int color, int max, int other, int iteration);
#endif
