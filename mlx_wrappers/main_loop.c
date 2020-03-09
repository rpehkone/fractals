/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 20:58:30 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/09 16:02:46 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	main_loop(void **mlx)
{
	mlx_clear_image(mlx);
	mlx_clear_window(mlx[0], mlx[1]);
	engine();
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], 0, 0);
}
