/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 10:46:58 by rpehkone          #+#    #+#             */
/*   Updated: 2019/11/02 14:24:58 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	tmp[len];

	if (!src)
		return (NULL);
	i = -1;
	s = (unsigned char*)src;
	d = (unsigned char*)dst;
	while (++i < len)
		tmp[i] = s[i];
	i = -1;
	while (++i < len)
		d[i] = tmp[i];
	return (dst);
}
