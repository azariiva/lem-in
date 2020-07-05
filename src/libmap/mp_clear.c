/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:00:02 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/02 15:39:22 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmap.h"
#include <limits.h>

static int	mp_isdeadlock(t_room *room)
{
	t_list	*v;
	int		isdeadlock;

	isdeadlock = 1;
	v = room->links;
	while (v)
	{
		if ((*(t_room **)v->content)->weight == INT_MAX || \
		((*(t_room **)v->content)->name && !mp_isdeadlock(*(t_room **)v->content)))
			isdeadlock = 0;
		v = v->next;
	}
	if (isdeadlock)
		ft_strdel(&(room->name));
	return (isdeadlock);
}

static void	linkdel(void *content, size_t size)
{
	if (size)
		ft_memdel(&content);
}

static void	rodel(void *content, size_t size)
{
	if (size)
	{
		ro_free((t_room **)content);
		ft_memdel(&content);
	}
}

static void	mp_rmbadlinks(t_room *room)
{
	t_list	*links;
	t_list	*todel;

	while (room->links && !(*(t_room **)room->links->content)->name)
	{
		todel = room->links;
		room->links = room->links->next;
		ft_lstdelone(&todel, linkdel);
	}
	if (!room->links)
		return ;
	links = room->links;
	while (links->next)
	{
		if (!(*(t_room **)links->next->content)->name)
		{
			todel = links->next;
			links->next = links->next->next;
			ft_lstdelone(&todel, linkdel);
		}
		else
			links = links->next;
	}
}

static void	mp_rmbadrooms(t_map *map)
{
	t_list	*middle;
	t_list	*todel;

	mp_rmbadlinks(map->start);
	middle = map->middle;
	while (middle)
	{
		mp_rmbadlinks(*(t_room **)middle->content);
		middle = middle->next;
	}

	while (map->middle && !(*(t_room **)map->middle->content)->name)
	{
		todel = map->middle;
		map->middle = map->middle->next;
		ft_lstdelone(&todel, rodel);
	}
	if (!map->middle)
		return ;
	middle = map->middle;
	while (middle->next)
	{
		if (!(*(t_room **)middle->next->content)->name)
		{
			todel = middle->next;
			middle->next = middle->next->next;
			ft_lstdelone(&todel, rodel);
		}
		else
			middle = middle->next;
	}
}

int			mp_clear(t_map *map)
{
	if (mp_isdeadlock(map->start))
		return (ERR);
	mp_rmbadrooms(map);
	return (OK);
}
