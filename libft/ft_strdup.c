/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 16:00:45 by rpehkone          #+#    #+#             */
/*   Updated: 2019/11/13 20:32:23 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	unsigned long	size;
	char			*copy;

	size = 0;
	while (s1[size])
		size++;
	if (!(copy = (char*)malloc(sizeof(copy) * (size + 1))))
		return (NULL);
	size = 0;
	while (s1[size])
	{
		copy[size] = s1[size];
		size++;
	}
	copy[size] = '\0';
	return (copy);
}
