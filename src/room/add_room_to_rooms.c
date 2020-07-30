/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_room_to_rooms.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 20:57:09 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/30 18:52:05 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"

static int	increase_size(t_room **rooms, size_t *size)
{
	size_t 	new_size;
	t_room	*new_rooms;

	new_size = (*size) * 2;
	if (!(new_rooms = ft_memalloc(sizeof(t_room) * new_size)))
		return (ERR);
	ft_memcpy(new_rooms, *rooms, sizeof(t_room) * (*size));
	ft_memdel((void **)rooms);
	*size = new_size;
	*rooms = new_rooms;
	return (OK);
}

int			check_rooms(t_room *rooms, t_room *room, size_t place)
{
	size_t 	i;

	i = -1;
	while (++i < place)
		if (rooms[i].name != NULL && (!ft_strcmp(rooms[i].name, room->name)
		|| (rooms[i].x == room->x && rooms[i].y == room->y)))
			return (ERR);
	return (OK);
}

int			add_room_to_rooms(t_room **rooms, t_room *room, size_t *size,
size_t *place)
{
	if (room->weight == 1)
	{
		if (check_rooms(*rooms, room, *place) == ERR || (*rooms)[0].name)
			return (ERR);
		roomcpy(*rooms, room);
	}
	else if (room->weight == 2)
	{
		if (check_rooms(*rooms, room, *place) == ERR || (*rooms)[1].name)
			return (ERR);
		roomcpy(*rooms + 1, room);
	}
	else
	{
		if (check_rooms(*rooms, room, *place) == ERR)
			return (ERR);
		roomcpy(*rooms + *place, room);
		if (++(*place) >= *size)
			increase_size(rooms, size);
	}
	ft_bzero(room, sizeof(t_room));
	return (OK);
}
