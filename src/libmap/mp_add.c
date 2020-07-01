/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:22:48 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/01 22:47:09 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmap.h"
#include <unistd.h>

int		mp_add(t_map *map, t_room *room, t_rtype rtype)
{
	t_list	*new;

	if (!room)
	{
		ft_putendl_fd("Error: mp_add null room pointer", STDERR_FILENO);
		return (ERR);
	}
	if (rtype == MIDDLE_ROOM)
	{
		if (!(new = ft_lstnew(&room, sizeof(t_room *))))
		{
			ft_putendl_fd("Error: mp_add allocation error", STDERR_FILENO);
			return (ERR);
		}
		ft_lstadd(&(map->middle), new);
	}
	else
	{
		if (rtype & START_ROOM)
		{
			if (map->start)
			{
				ft_putendl_fd("Error: mp_add double start room", STDERR_FILENO);
				return (ERR);
			}
			map->start = room;
		}
		if (rtype & END_ROOM)
		{
			if (map->end)
			{
				ft_putendl_fd("Error: mp_add double end room", STDERR_FILENO);
				return (ERR);
			}
			map->end = room;
		}
	}
	return (OK);
}
