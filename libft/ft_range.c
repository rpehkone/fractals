/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 11:48:24 by rpehkone          #+#    #+#             */
/*   Updated: 2019/10/31 15:27:29 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_range(int min, int max)
{
	int	*res;
	int	i;

	i = 0;
	if (min >= max)
		return (0);
	while (i < max - min)
		i++;
	if (!(res = (int*)malloc(1 + i * sizeof(int))))
		return (0);
	i = 0;
	while (min < max)
		res[i++] = min++;
	return (res);
}
