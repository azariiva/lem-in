/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 17:14:53 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 03:56:43 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libam.h"
#include <unistd.h>

static void	del(void *content, size_t size)
{
	if (content && size)
		ft_memdel(&content);
}

static void	full_del(void *content, size_t size)
{
	if (content && size)
	{
		ro_del((t_room **)content);
		ft_memdel(&content);
	}
}

static int	am_addrooms(t_am *am, t_list *rooms, t_room *start, t_room *end)
{
	size_t	i;

	if (!start || !end)
		return (ERR);
	am->size = ft_lstsize(rooms) + 2;
	am->rooms = ft_memalloc(am->size * sizeof(t_room *));
	am->edges = ft_memalloc(am->size * sizeof(int *));
	am->flow = ft_memalloc(am->size * sizeof(int *));
	am->addgraph = ft_memalloc(am->size * sizeof(int *));
	i = -1;
	while (++i < am->size)
	{
		am->edges[i] = ft_memalloc(am->size * sizeof(int));
		am->flow[i] = ft_memalloc(am->size * sizeof(int));
		am->addgraph[i] = ft_memalloc(am->size * sizeof(int));
	}
	am->rooms[0] = start;
	am->rooms[am->size - 1] = end;
	i = 0;
	while (++i < am->size - 1)
	{
		am->rooms[i] = *(t_room **)rooms->content;
		rooms = rooms->next;
	}
	return (OK);
}

int			check_room_coords(t_room *room, t_list *rooms)
{
	t_list	*ptr;

	ptr = rooms;
	while (ptr)
	{
		if (co_equal(room->coord, (*(t_room **)ptr->content)->coord))
			return (ERR);
		ptr = ptr->next;
	}
	return (OK);
}

t_am		*am_new(int fd)
{
	t_am	*am;
	t_list	*rooms;
	t_list	*new;
	t_room	*room;
	t_room	*ser[2];

	char	*line;

	ser[0] = NULL;
	ser[1] = NULL;
	rooms = NULL;
	if (!(am = ft_memalloc(sizeof(t_am))))
		return (NULL);
	am_gnl(fd, &line);
	if ((am->ants = ft_atoi(line)) <= 0)
	{
		am_del(&am);
		am_gnl(-1, NULL);
		return (NULL);
	}
	while (am_gnl(fd, &line) == OK && !ft_strchr(line, '-'))
	{
		if ((room = ro_atoroom(line)) == (t_room *)ERR)
		{
			ro_del(ser);
			ro_del(ser + 1);
			am_del(&am);
			ft_lstdel(&rooms, full_del);
			am_gnl(-1, NULL);
			return (NULL);
		}
		else if (room != (t_room *)OK)
		{
			if (check_room_coords(room, rooms) == ERR ||
			(ser[0] && co_equal(room->coord, ser[0]->coord)) ||
			(ser[1] && co_equal(room->coord, ser[1]->coord)))
			{
				ro_del(ser);
				ro_del(ser + 1);
				am_del(&am);
				ft_lstdel(&rooms, full_del);
				am_gnl(-1, NULL);
				return (NULL);
			}

			if (room->weight == START_ROOM)
				ser[0] = room;
			else if (room->weight == END_ROOM)
				ser[1] = room;
			else if (!(new = ft_lstnew(&room, sizeof(t_room **))))
			{
				ro_del(ser);
				ro_del(ser + 1);
				am_del(&am);
				ro_del(&room);
				ft_lstdel(&rooms, full_del);
				am_gnl(-1, NULL);
				return (NULL);
			}
			else
				ft_lstadd(&rooms, new);
		}
	}
	if (!ft_strchr(line, '-'))
	{
		ro_del(ser);
		ro_del(ser + 1);
		ft_lstdel(&rooms, full_del);
		am_del(&am);
		am_gnl(-1, NULL);
		return (NULL);
	}
	if (am_addrooms(am, rooms, ser[0], ser[1]) == ERR)
	{
		ro_del(ser);
		ro_del(ser + 1);
		ft_lstdel(&rooms, full_del);
		am_del(&am);
		am_gnl(-1, NULL);;
		return (NULL);
	}
	ft_lstdel(&rooms, del);
	while (OK)
	{
		if (am_addlink(line, am) == ERR)
		{
			am_del(&am);
			am_gnl(-1, NULL);
			return (NULL);
		}
		if (am_gnl(fd, &line) != OK)
			break ;
	}
	am_gnl(-1, NULL);
	return (am);
}
