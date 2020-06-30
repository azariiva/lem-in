/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_giveweight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:31:19 by blinnea           #+#    #+#             */
/*   Updated: 2020/06/30 21:32:18 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmap.h"

static void	walk(t_room *room)
{
	t_list	*ptr;

	room->visited = 1;
	ptr = room->links;
	while (ptr)
	{
		if ((*(t_room **)ptr->content)->weight > room->weight + 1)
			(*(t_room **)ptr->content)->weight = room->weight + 1;
		ptr = ptr->next;
	}
	ptr = room->links;
	while (ptr)
	{
		if (!(*(t_room **)ptr->content)->visited)
			walk(*(t_room **)ptr->content);
		ptr = ptr->next;
	}
}

static void	helper(t_room *room)
{
	t_list	*ptr;

	ptr = room->links;
	while (ptr)
	{
		if ((*(t_room **)ptr->content)->weight + 1 < room->weight)
			room->weight = (*(t_room **)ptr->content)->weight + 1;
		ptr = ptr->next;
	}
}

void		mp_giveweight(t_map *map)
{
	t_list	*ptr;

	map->start->weight = 0;
	walk(map->start);
	ptr = map->middle;
	while (ptr)
	{
		helper(*(t_room *)ptr->content);
		ptr = ptr->next;
	}
}
