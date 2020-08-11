/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:02:30 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/11 16:47:53 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# include "mlx_io.h"
# include <pthread.h>
# include <math.h>
# define THREAD_AMOUNT 6
# define PRECISION long double
# define WIDTH 1280
# define HEIGHT 720
# define ASPECT_WIDTH 16.0
# define ASPECT_HEIGHT 9.0

typedef struct		s_position_xy {
	PRECISION		x;
	PRECISION		y;
}					t_position_xy;

typedef struct		s_settings {
	t_position_xy	pos;
	PRECISION		zoom;
	int				max_iter;
	int				max_i_modifier;
	int				color;
	int				frame;
	int				fractal_id;
	void			(*fractal)(struct s_settings*, int, int);
}					t_settings;

void				mandelbrot(t_settings *settings, int start, int stop);
void				julia(t_settings *settings, int start, int stop);
void				burningship(t_settings *settings, int start, int stop);
t_settings			*init_settings(int i);
void				color_settings(t_settings *settings);
int					select_color(int color, int max, int frame, int iteration);
#endif
