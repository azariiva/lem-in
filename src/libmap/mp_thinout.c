/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_thinout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:49:40 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/02 00:41:14 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmap.h"

static void	del(void *content, size_t size)
{
	if (!size)
		ft_memdel(&content);
}

static void	helper1(t_list **links)
{
	t_list	*ptr;
	t_list	*todel;

	while ((*links) && (*links)->content_size == 0)
	{
		todel = *links;
		*links = todel->next;
		ft_lstdelone(&todel, del);
	}
	if (!*links)
		return ;
	ptr = *links;
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

// static void	del(void *content, size_t size)
// {
// 	if (size && content)
// 		ro_free((t_room **)content);
// }

// static void	helper2(t_list **middle)
// {
// 	t_list	*ptr;
// 	t_list	*todel;
// 	int		flag;

// 	flag = 1;
// 	while (flag)
// 	{
// 		flag = 0;
// 		while (!(*((t_room **)(*middle)->content))->links)
// 		{
// 			todel = *middle;
// 			*middle = (*middle)->next;
// 			ft_lstdelone(&todel, del);

// 		}
// 		ptr = *middle;
// 		while (ptr->next)
// 		{
// 			if (!(*((t_room **)ptr->next->content))->links)
// 			{
// 				todel = ptr->next;
// 				ptr->next = ptr->next->next;
// 				ft_lstdelone(&todel, del);
// 			}
// 		}
// 	}
// }

static void	walk(t_room *room)
{
	t_list	*ptr;


	room->visited = 2;
	ptr = room->links;
	while (ptr)
	{
		if ((*(t_room **)ptr->content)->visited != 2)
			walk(*(t_room **)ptr->content);
		if ((*(t_room **)ptr->content)->weight <= room->weight)
			ptr->content_size = 0; // means that we should remove it later
		ptr = ptr->next;
	}
}

void		mp_thinout(t_map *map)
{
	t_list	*ptr;

	map->start->visited = 2;
	ptr = map->start->links;
	while (ptr)
	{
		walk(*(t_room **)ptr->content);
		ptr = ptr->next;
	}
	walk(map->end);
	ptr = map->middle;
	while (ptr)
	{
		helper1(&((*(t_room **)ptr->content)->links));
		ptr = ptr->next;
	}
	helper1(&(map->end->links));
	// helper2(&(map->middle));
}
