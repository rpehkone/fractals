/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_io.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/06 11:33:04 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_IO_H
# define MLX_IO_H
# include "mlx.h"
# include "libft.h"

typedef struct	s_int_xy {
	int			x;
	int			y;
}				t_int_xy;

int				handle_keyboard_down(int key);
int				handle_keyboard_up(int key);
int				handle_mouse_down(int button, int x, int y);
int				handle_mouse_up(int button, int x, int y);
int				handle_cursor(int x, int y);
int				loop_hook(void);
void			**get_mlx(void **mlx);
t_int_xy		get_window_size(void);
t_int_xy		set_cursor(int call, int x, int y);
int				set_mouse(int call, int button);
int				set_key(int call, int key);
void			fractal(void);
void			init_window(int width, int height, char *filename);
void			update_image(void);
void			pixel_put(int x, int y, unsigned color);
int				is_mouse_down(int button);
int				is_key_down(int key);
t_int_xy		get_cursor(void);
#endif
