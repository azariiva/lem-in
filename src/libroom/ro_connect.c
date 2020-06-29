/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ro_ro_connect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 19:36:16 by blinnea           #+#    #+#             */
/*   Updated: 2020/06/28 22:53:13 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libroom.h"

static int	is_ro_connected(t_room *a, t_room *b)
{
	t_list	*ptr;

	ptr = a->links;
	while (ptr)
	{
		if (*(t_room **)(ptr->content) == b)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

int			ro_connect(t_room *a, t_room *b, t_linktype linktype)
{
	t_list	*new;
	if (is_ro_connected(a, b))
	{
		ft_putendl_fd("Error: ro_connect double link", STDERR_FILENO);
		return (ERR);
	}
	if (!(new = ft_lstnew(&b, sizeof(t_room *))))
	{
		ft_putendl_fd("Error: ro_connect allocation error", STDERR_FILENO);
		return (ERR);
	}
	ft_lstadd(&(a->links), new);
	if (linktype == DOUBLE_LINK)
	{
		if (!(new = ft_lstnew(&a, sizeof(t_room *))))
		{
			ft_putendl_fd("Error: ro_connect allocation error", STDERR_FILENO);
			return (ERR);
		}
		ft_lstadd(&(b->links), new);
	}
	return (OK);
}
