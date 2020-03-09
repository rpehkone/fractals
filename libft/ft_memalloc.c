/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 15:22:24 by rpehkone          #+#    #+#             */
/*   Updated: 2019/11/07 13:27:55 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*fresh;

	if (!(fresh = (char*)malloc(sizeof(fresh) * (size))))
		return (NULL);
	while (size--)
		fresh[size] = 0;
	return ((void*)fresh);
}
