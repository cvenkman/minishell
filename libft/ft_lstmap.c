/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:51:21 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 21:51:21 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first_elm_res;
	t_list	*cur_elm_res;

	if (lst == NULL)
		return (NULL);
	first_elm_res = ft_lstnew(f(lst->content));
	if (first_elm_res == NULL)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		cur_elm_res = f(lst->content);
		if (cur_elm_res == NULL)
		{
			ft_lstclear(&first_elm_res, del);
			return (NULL);
		}
		ft_lstadd_back(&first_elm_res, ft_lstnew(cur_elm_res));
		lst = lst->next;
	}
	return (first_elm_res);
}
