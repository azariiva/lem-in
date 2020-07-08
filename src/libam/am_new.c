/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 17:14:53 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/08 18:54:03 by blinnea          ###   ########.fr       */
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
	{
		ft_printf_fd(STDERR_FILENO, "{red}Error:{eoc} no start or end.\n");
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
	t_list	*new;
	t_room	*room;
	t_room	*ser[2];

	char	*line;

	ser[0] = NULL;
	ser[1] = NULL;
	rooms = NULL;
	if (!(am = ft_memalloc(sizeof(t_am))))
	{
		ft_printf_fd(STDERR_FILENO, "{red}Error:{eoc} allocation error.\n");
		return (NULL);
	}
	get_next_line(fd, &line);
	if (!(am->ants = ft_atoi(line)))
	{
		ft_printf_fd(STDERR_FILENO, "{red}Error:{eoc} no ants.\n");
		am_del(&am);
		ft_strdel(&line);
		get_next_line(-1, NULL);
		return (NULL);
	}
	ft_strdel(&line);
	while (get_next_line(fd, &line) == OK && !ft_strchr(line, '-'))
	{
		if ((room = ro_atoroom(line)) == (t_room *)ERR)
		{
			ro_del(ser);
			ro_del(ser + 1);
			am_del(&am);
			ft_lstdel(&rooms, full_del);
			ft_strdel(&line);
			get_next_line(-1, NULL);
			return (NULL);
		}
		else if (room != (t_room *)OK)
		{
			if (room->weight == START_ROOM)
				ser[0] = room;
			else if (room->weight == END_ROOM)
				ser[1] = room;
			else if (!(new = ft_lstnew(&room, sizeof(t_room **))))
			{
				ft_printf_fd(STDERR_FILENO, "{red}Error:{eoc} allocation error.");
				ro_del(ser);
				ro_del(ser + 1);
				am_del(&am);
				ro_del(&room);
				ft_lstdel(&rooms, full_del);
				ft_strdel(&line);
				get_next_line(-1, NULL);
				return (NULL);
			}
			else
				ft_lstadd(&rooms, new);
		}
		ft_strdel(&line);
	}
	if (!ft_strchr(line, '-'))
	{
		ft_printf_fd(STDERR_FILENO, "{red}Error:{eoc} no links between rooms.\n");
		ro_del(ser);
		ro_del(ser + 1);
		ft_lstdel(&rooms, full_del);
		am_del(&am);
		ft_strdel(&line);
		get_next_line(-1, NULL);
		return (NULL);
	}
	if (am_addrooms(am, rooms, ser[0], ser[1]) == ERR)
	{
		ft_strdel(&line);
		ro_del(ser);
		ro_del(ser + 1);
		ft_lstdel(&rooms, full_del);
		am_del(&am);
		get_next_line(-1, NULL);;
		return (NULL);
	}
	ft_lstdel(&rooms, del);
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
