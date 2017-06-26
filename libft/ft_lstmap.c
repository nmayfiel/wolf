/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 17:30:33 by nmayfiel          #+#    #+#             */
/*   Updated: 2016/11/25 19:14:54 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_list;
	t_list	*ret;

	new_list = (*f)(lst);
	if (!new_list)
		return (NULL);
	ret = new_list;
	lst = lst->next;
	while (lst != NULL)
	{
		new_list->next = (*f)(lst);
		new_list = new_list->next;
		if (!new_list)
			return (NULL);
		lst = lst->next;
	}
	return (ret);
}
