/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_thinout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:49:40 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/02 15:19:17 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmap.h"

static void	del(void *content, size_t size)
{
	if (!size)
		ft_memdel(&content);
}

static void	helper(t_room *room)
{
	t_list	*ptr;
	t_list	*todel;

	while (room->links && room->links->content_size == 0)
	{
		todel = room->links;
		room->links = room->links->next;
		ft_lstdelone(&todel, del);
	}
	if (!room->links)
		return ;
	ptr = room->links;
	while (ptr->next)
	{
		if (ptr->next->content_size == 0)
		{
			todel = ptr->next;
			ptr->next = ptr->next->next;
			ft_lstdelone(&todel, del);
		}
		else
			ptr = ptr->next;
	}
}


void		mp_thinout(t_map *map)
{
	t_list	*link;
	t_list	*list_room;
	t_room	*room;

	list_room = map->middle;
	while (list_room)
	{
		room = *(t_room **)list_room->content;
		link = room->links;
		while (link)
		{
			if ((*(t_room **)link->content)->weight <= room->weight)
				link->content_size = 0;
			link = link->next;
		}
		list_room = list_room->next;
	}
	list_room = map->middle;
	while (list_room)
	{
		helper(*(t_room **)list_room->content);
		list_room = list_room->next;
	}
	mp_clear(map);
}
