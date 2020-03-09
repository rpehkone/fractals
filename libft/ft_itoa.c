/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:58:41 by rpehkone          #+#    #+#             */
/*   Updated: 2019/11/13 20:48:39 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*res;
	size_t	size;
	long	neg;

	neg = n;
	size = (neg > 0) ? 0 : 1;
	neg = (neg > 0) ? neg : -neg;
	while (n)
		n = size++ ? n / 10 : n / 10;
	if (!(res = (char *)malloc(sizeof(res) * size + 1)))
		return (NULL);
	*(res + size--) = '\0';
	while (neg > 0)
	{
		*(res + size--) = neg % 10 + '0';
		neg /= 10;
	}
	if (size == 0 && res[1] == '\0')
		*(res + size) = '0';
	if (size == 0 && res[1] != '\0')
		*(res + size) = '-';
	return (res);
}
