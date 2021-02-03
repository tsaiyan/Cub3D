/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:37:58 by tsaiyan           #+#    #+#             */
/*   Updated: 2020/10/31 14:38:00 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*lstnew;

	if (!lst || !f)
		return (NULL);
	if (!(lstnew = ft_lstnew(f(lst->content))))
		return (NULL);
	newlist = lstnew;
	lst = lst->next;
	while (lst)
	{
		if (!(lstnew = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&newlist, del);
			ft_lstclear(&lstnew, del);
			return (0);
		}
		ft_lstadd_back(&newlist, lstnew);
		lst = lst->next;
	}
	return (newlist);
}
