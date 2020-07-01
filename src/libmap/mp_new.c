/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:57:51 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/01 22:48:00 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmap.h"
#include <unistd.h>

static int	read_rooms(int fd, t_map *map)
{
	char	*line;
	int		rcode;
	int		rtype;
	char	*trimmed;

	rtype = MIDDLE_ROOM;
	while ((rcode = get_next_line(fd, &line)) == OK)
	{
		if (line[0] == '#')
		{
			if (line[1] == '#')
			{
				trimmed = ft_strtrim(line);
				if (!ft_strcmp(trimmed + 2, "start"))
					rtype |= START_ROOM;
				else if (!ft_strcmp(trimmed + 2, "end"))
					rtype |= END_ROOM;
				ft_strdel(&trimmed);
			}
		}
		else if (line[0] == 'L')
		{
			ft_putendl_fd("Error: letter \'L\' in input line", STDERR_FILENO);
			ft_strdel(&line);
			return (ERR);
		}
		else if (ft_strchr(line, '-') != NULL)
		{
			if (!map->start || !map->end)
			{
				ft_putendl_fd("Error: read_rooms start or end doesn't exist",\
				STDERR_FILENO);
				return (ERR);
			}
			rcode = mp_atolink(map, line);
			ft_strdel(&line);
			return (rcode);
		}
		else
		{
			if (mp_add(map, ro_atoroom(line), rtype) == ERR)
				return (ERR);
			rtype = MIDDLE_ROOM;
		}
		ft_strdel(&line);
	}
	return (rcode);
}

static int	read_links(int fd, t_map *map)
{
	char	*line;
	int		rcode;

	while ((rcode = get_next_line(fd, &line)) == OK)
	{
		if (line[0] != '#' && mp_atolink(map, line) == ERR)
		 	return (ERR);
		ft_strdel(&line);
	}
	return (rcode);
}

t_map		*mp_new(int fd)
{
	t_map	*map;

	if (!(map = ft_memalloc(sizeof(t_map))))
	{
		ft_putendl_fd("Error: mp_new allocation error", STDERR_FILENO);
		return (NULL);
	}
	if (read_rooms(fd, map) == ERR || read_links(fd, map) == ERR)
		mp_free(&map);
	get_next_line(-1, NULL);
	return (map);
}
