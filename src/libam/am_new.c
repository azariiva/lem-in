/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 17:14:53 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/06 21:14:54 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libam.h"
#include <unistd.h>

static int	am_addrooms(t_am *am, t_list *rooms, t_room *start, t_room *end)
{
	size_t	i;

	if (!start || !end)
	{
		ft_putendl_fd("Error: no start or end", STDERR_FILENO);
		return (ERR);
	}
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

t_am		*am_new(int fd)
{
	t_am	*am;
	t_list	*rooms;
	t_room	*room;
	t_room	*ser[2];

	char	*line;

	ser[0] = NULL;
	ser[1] = NULL;
	rooms = NULL;
	if (!(am = ft_memalloc(sizeof(t_am))))
		return (NULL);
	get_next_line(fd, &line);
	if (!(am->ants = ft_atoi(line)))
	{
		ft_printf_fd(STDERR_FILENO, "{red}Error:{eoc} no ants.");
		return (NULL);
	}
	while (get_next_line(fd, &line) == OK && !ft_strchr(line, '-'))
	{
		if ((room = ro_atoroom(line)))
		{
			if (room->weight == START_ROOM)
				ser[0] = room;
			else if (room->weight == END_ROOM)
				ser[1] = room;
			else
				ft_lstadd(&rooms, ft_lstnew(&room, sizeof(t_room **)));
		}
		ft_strdel(&line);
	}
	if (!ft_strchr(line, '-'))
	{
		ft_printf_fd(STDERR_FILENO, "{red}Error:{eoc} no links between rooms.");
		am_del(&am);
		get_next_line(-1, NULL);
		return (NULL);
	}
	am_addrooms(am, rooms, ser[0], ser[1]);

	while (OK)
	{
		if (am_addlink(line, am) == ERR)
		{
			ft_strdel(&line);
			am_del(&am);
			get_next_line(-1, NULL);
			return (NULL);
		}
		ft_strdel(&line);
		if (get_next_line(fd, &line) != OK)
			break;
	}
	get_next_line(-1, NULL);
	return (am);
}
