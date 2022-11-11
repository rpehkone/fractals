/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2022/11/11 18:56:43 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	*split_screen(void *settings)
{
	static int	s = 0;

	s++;
	if (s >= THREAD_AMOUNT)
	{
		((t_settings*)settings)->fractal(((t_settings*)settings),
			(HEIGHT / THREAD_AMOUNT) * (s - 1), HEIGHT);
		s = 0;
	}
	else
		((t_settings*)settings)->fractal(((t_settings*)settings),
			(HEIGHT / THREAD_AMOUNT) * (s - 1), (HEIGHT / THREAD_AMOUNT) * s);
	return (NULL);
}

void	print_fractal(t_settings *settings)
{
	pthread_t	tid[THREAD_AMOUNT];
	int			i;

	i = 0;
	while (i < THREAD_AMOUNT)
	{
		pthread_create(&tid[i], NULL, split_screen, (void*)settings);
		usleep(1000);
		i++;
	}
	i = 0;
	while (i < THREAD_AMOUNT)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
}

void	handle_settings(t_settings *settings, t_int_xy c, t_int_xy oldc)
{
	if (is_mouse_down(M_CLK_L) && settings->fractal_id != 2)
		settings->pos.x -= ((PRECISION)c.x - oldc.x) * settings->zoom;
	if (is_mouse_down(M_CLK_L) && settings->fractal_id != 2)
		settings->pos.y -= ((PRECISION)c.y - oldc.y) * settings->zoom;
	if (is_key_down(K_AR_L) && settings->fractal_id != 2)
		settings->pos.x -= settings->zoom * 20;
	if (is_key_down(K_AR_R) && settings->fractal_id != 2)
		settings->pos.x += settings->zoom * 20;
	if (is_key_down(K_AR_D) && settings->fractal_id != 2)
		settings->pos.y += settings->zoom * 20;
	if (is_key_down(K_AR_U) && settings->fractal_id != 2)
		settings->pos.y -= settings->zoom * 20;
	settings->max_iter = 15 + 120 *
		(logl((PRECISION)settings->zoom) / logl(0.0000000000000000005));
	if (is_key_down(K_A))
		settings->max_i_modifier = 0;
	if (is_key_down(K_S))
		settings->max_i_modifier += 1;
	if (is_key_down(K_D))
		settings->max_i_modifier -= 1;
	if (settings->max_i_modifier < -120)
		settings->max_i_modifier = -120;
	else if (settings->max_i_modifier > 120)
		settings->max_i_modifier = 120;
	settings->max_iter += settings->max_i_modifier;
}

void	handle_zoom(t_settings *settings, t_int_xy c)
{
	if ((is_mouse_down(M_CLK_R) || is_mouse_down(M_SCR_U)))
	{
		settings->zoom = settings->zoom * (1.0 / 1.08);
		if (settings->zoom < 0.00000000000000000050)
			settings->zoom = 0.00000000000000000050;
		if (settings->fractal_id == 2)
			return ;
		if (settings->zoom > 0.00000000000000000050)
			settings->pos.x += (c.x - WIDTH / 2) * (0.15 * settings->zoom);
		if (settings->zoom > 0.00000000000000000050)
			settings->pos.y += (c.y - HEIGHT / 2) * (0.15 * settings->zoom);
	}
	if ((is_mouse_down(M_CLK_R) || is_mouse_down(M_SCR_D)))
	{
		settings->zoom = settings->zoom * 1.08;
		if (settings->zoom > 3)
			settings->zoom = 3;
		if (settings->fractal_id == 2)
			return ;
		if (settings->zoom < 3)
			settings->pos.x += (c.x - WIDTH / 2) * (0.15 * settings->zoom);
		if (settings->zoom < 3)
			settings->pos.y += (c.y - HEIGHT / 2) * (0.15 * settings->zoom);
	}
}

void		frac_rotate(t_position_xy *direction, double angle)
{
	double		sin_angle;
	double		cos_angle;
	PRECISION	x;
	PRECISION	y;

	sin_angle = sin(angle);
	cos_angle = cos(angle);
	x = direction->x;
	y = direction->y;
	direction->x = x * cos_angle + y * sin_angle;
	direction->y = y * cos_angle - x * sin_angle;
}

t_int_xy	spinner(void)
{
	static t_position_xy	fake_cursor = {.x = 512 / 4, .y = 512 / 4};
	t_int_xy				res;

	frac_rotate(&fake_cursor, -0.01);
	res.x = 512 / 2 + (int)fake_cursor.x;
	res.y = 512 / 2 + (int)fake_cursor.y;
	return (res);
}

void	fractal(void)
{
	static t_settings	*settings = NULL;
	static t_int_xy		oldc;
	t_int_xy			cursor;

	if (is_key_down(K_ESC))
		exit(0);
	if (!settings)
		settings = init_settings(0);
	update_image();
	cursor = get_cursor();
	// cursor = spinner();
	if (settings->fractal_id == 2)
	{
		settings->pos.x -= ((PRECISION)cursor.x - oldc.x);
		settings->pos.y -= ((PRECISION)cursor.y - oldc.y);
	}
	handle_settings(settings, cursor, oldc);
	if (settings->max_iter < 0)
		settings->max_iter = 0;
	else if (settings->max_iter > 120)
		settings->max_iter = 120;
	handle_zoom(settings, cursor);
	color_settings(settings);
	oldc.x = cursor.x;
	oldc.y = cursor.y;
	print_fractal(settings);
}
