/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:19:34 by rpehkone          #+#    #+#             */
/*   Updated: 2019/10/28 17:51:55 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	char	str[11];
	int		tmp;
	int		size;

	size = 0;
	if (n == 0)
		ft_putchar('0');
	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else if (n < 0)
		if (n *= -1)
			ft_putchar('-');
	tmp = n;
	while (tmp > 0 && ++size)
		tmp /= 10;
	str[size] = '\0';
	while (size--)
	{
		str[size] = n % 10 + '0';
		n /= 10;
	}
	size++;
	while (str[size])
		ft_putchar(str[size++]);
}
