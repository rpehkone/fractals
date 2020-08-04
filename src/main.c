/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/04 16:17:53 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	*split_screen(void *args)
{
	static int			start = 0;
	static int			stop = 0;
	struct sched_param	params;

	params.sched_priority = sched_get_priority_max(SCHED_FIFO);
	pthread_setschedparam(pthread_self(), SCHED_FIFO, &params);
	stop += HEIGHT / THREAD_COUNT;
	if (((t_args*)args)->fractal_id == 1)
		mandelbrot((t_args*)args, start, stop);
	else if (((t_args*)args)->fractal_id == 2)
		julia((t_args*)args, start, stop);
	else if (((t_args*)args)->fractal_id == 3)
	{
		((t_args*)args)->color = 6;
		((t_args*)args)->pos.x = -175;
		((t_args*)args)->pos.y = -3;
		((t_args*)args)->zoom = 0.0117;
		((t_args*)args)->pos2.x = -175;
		((t_args*)args)->pos2.y = -3;
		((t_args*)args)->zoom2 = 0.0117;
		burningship((t_args*)args, start, stop);
	}
	start += HEIGHT / THREAD_COUNT;
	return (NULL);
}

void	init_args(t_args *args)
{
	args->pos.x = 0;
	args->pos.y = 0;
	args->pos2.x = 0;
	args->pos2.y = 0;
	args->zoom2 = .3;
	args->max_iter2 = 50;
	args->zoom = .3;
	args->max_iter = 50;
	args->sync_threads = 1;
	args->buffer_id = 0;
	args->threads_ready = 0;
	args->color = 5;
}

t_args	*init_fractal(int f)
{
	int				i;
	pthread_t		tid[THREAD_COUNT];
	static t_args	args;

	init_args(&args);
	if (f)
	{
		args.fractal_id = f;
		return (NULL);
	}
	if (!(args.dbuffer = (int**)malloc(sizeof(int*) * 2)))
		exit(0);
	if (!(args.dbuffer[0] = (int*)malloc(sizeof(int) * (WIDTH * HEIGHT))))
		exit(0);
	if (!(args.dbuffer[1] = (int*)malloc(sizeof(int) * (WIDTH * HEIGHT))))
		exit(0);
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_create(&tid[i], NULL, split_screen, (void*)&args);
		usleep(10000);
		i++;
	}
	return (&args);
}

void	put_usage(char *arg)
{
	ft_putstr("usage: ");
	ft_putstr(arg);
	ft_putstr(" [mandelbrot | julia | burningship]\n");
}

int		main(int argc, char **argv)
{
	if (argc < 2)
		put_usage(argv[0]);
	else if (!ft_strcmp(argv[1], "mandelbrot"))
	{
		init_fractal(1);
		init_window(WIDTH, HEIGHT, "mandlelbrot");
	}
	else if (!ft_strcmp(argv[1], "julia"))
	{
		init_fractal(2);
		init_window(WIDTH, HEIGHT, "julia");
	}
	else if (!ft_strcmp(argv[1], "burningship"))
	{
		init_fractal(3);
		init_window(WIDTH, HEIGHT, "burningship");
	}
	else
		put_usage(argv[0]);
	return (0);
}
