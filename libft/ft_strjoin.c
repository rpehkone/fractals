/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:42:39 by rpehkone          #+#    #+#             */
/*   Updated: 2019/11/13 20:32:08 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*fresh;
	int		i;
	int		j;
	int		len_1;
	int		len_2;

	i = 0;
	j = 0;
	len_1 = 0;
	len_2 = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s1[len_1])
		len_1++;
	while (s2[len_2])
		len_2++;
	if (!(fresh = (char*)malloc(sizeof(char) * (len_1 + len_2 + 1))))
		return (NULL);
	while (s1[j] != '\0')
		fresh[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		fresh[i++] = s2[j++];
	fresh[i] = '\0';
	return (fresh);
}
