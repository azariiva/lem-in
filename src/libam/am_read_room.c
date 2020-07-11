/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_read_room.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 06:42:37 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 06:45:44 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libam.h"

static int		check_room_coords(t_room *room, t_list *r)
{
	t_list	*ptr;

	ptr = r;
	while (ptr)
	{
		if (co_equal(room->c, (*(t_room **)ptr->content)->c))
			return (ERR);
		ptr = ptr->next;
	}
	return (OK);
}

int				am_read_room(char *line, t_list **r, t_room **ser)
{
	t_room	*room;
	t_list	*new;

	if ((room = ro_atoroom(line)) == (t_room *)ERR)
		return (ERR);
	if (room == (t_room *)OK)
		return (OK);
	if (check_room_coords(room, *r) == ERR ||
	(ser[0] && co_equal(room->c, ser[0]->c)) ||
	(ser[1] && co_equal(room->c, ser[1]->c)) ||
	(ser[0] && room->w == SR) || (ser[1] && room->w == ER))
	{
		ro_del(&room);
		return (ERR);
	}
	if (room->w != MIDDLE_ROOM)
		ser[(room->w == SR ? 0 : 1)] = room;
	else if (!(new = ft_lstnew(&room, sizeof(t_room **))))
	{
		ro_del(&room);
		return (ERR);
	}
	else
		ft_lstadd(r, new);
	return (OK);
}
