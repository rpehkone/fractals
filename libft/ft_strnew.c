/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 15:31:57 by rpehkone          #+#    #+#             */
/*   Updated: 2019/11/13 20:22:12 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*fresh;
	size_t	i;

	i = 0;
	if (!(fresh = (char*)malloc(sizeof(fresh) * (size + 1))))
		return (NULL);
	while (i < size)
		fresh[i++] = 0;
	fresh[size] = '\0';
	return (fresh);
}
