/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:36:33 by rpehkone          #+#    #+#             */
/*   Updated: 2019/11/07 16:35:15 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			size;
	char			*fresh;

	if (!s)
		return (0);
	size = 0;
	while (s[size])
		size++;
	if (!(fresh = (char*)malloc(sizeof(fresh) * (size))))
		return (NULL);
	fresh[size] = '\0';
	size = 0;
	while (*s)
	{
		fresh[size] = f(size, *s);
		s++;
		size++;
	}
	return (fresh);
}
