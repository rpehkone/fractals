/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:50:09 by rpehkone          #+#    #+#             */
/*   Updated: 2019/10/31 14:47:54 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *start;

	if (!(new = ft_lstnew(((f(lst))->content), f(lst)->content_size)))
		return (NULL);
	start = new;
	while (lst->next)
	{
		lst = lst->next;
		if (!(new->next = ft_lstnew(((f(lst))->content), f(lst)->content_size)))
			return (NULL);
		new = new->next;
	}
	return (start);
}
