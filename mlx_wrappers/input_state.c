/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 22:35:09 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/10 17:50:47 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_int_xy	get_cursor(void)
{
	return (set_cursor(0, 0, 0));
}

int			is_mouse_down(int button)
{
	return(set_mouse(0, button));
}

int			is_key_down(int key)
{
	return(set_key(0, key));
}


t_int_xy	set_cursor(int call, int x, int y)
{
	static t_int_xy	c = {.x = 0, .y = 0};

	if (call)
	{
		c.x = x;
		c.y = y;
	}
	return (c);
}

int			set_key(int call, int key)
{
	static int	*keyb = NULL;
	int			i;

	if (!keyb)
	{
		i = 0;
		if (!(keyb = (int*)malloc(sizeof(int) * 310)))
			ft_error(NULL);
		while (i < 300)
		{
			keyb[i] = 0;
			i++;
		}
	}
	if (call == 0)
		return (keyb[key]);
	else if (call == 1)
		keyb[key] = 1;
	else if (call == 2)
		keyb[key] = 0;
	return (0);
}

int			set_mouse(int call, int button)
{
	static int	*mouse = NULL;
	int			i;

	if (!mouse)
	{
		i = 0;
		if (!(mouse = (int*)malloc(sizeof(int) * 7)))
			ft_error(NULL);
		while (i < 6)
		{
			mouse[i] = 0;
			i++;
		}
	}
	if (call == 0)
		return (mouse[button]);
	else if (call == 1)
		mouse[button] = 1;
	else if (call == 2)
		mouse[button] = 0;
	return (0);
}
