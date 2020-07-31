/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhitmonc <lhitmonc@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 20:48:19 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/31 23:07:39 by lhitmonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"

static inline t_room	*exit__(char **line, t_room **rooms)
{
	if (line && *line)
		ft_strdel(line);
	if (rooms && *rooms)
		ft_memdel((void **)rooms);
	return (NULL);
}

static int				isroom(char *line)
{
	char	*ptr;
	int		ctr;

	if (line[0] == '#')
		return (1);
	ctr = 0;
	ptr = line;
	while (*ptr)
		if (ft_isspace(*ptr++))
			++ctr;
	return (ctr == 2);
}

t_room					*create_rooms(int fdin, int fdout, char **line,
size_t *size)
{
	t_room			*rooms;
	t_room			room;
	int				rc;
	size_t			place;

	ft_bzero(&room, sizeof(t_room));
	place = 2;
	*size = RDSIZE;
	if (!(rooms = ft_memalloc(sizeof(t_room) * (*size))))
		return (NULL);
	while (get_next_line(fdin, line) == OK &&
	isroom(*line))
	{
		ft_printf_fd(fdout, "%s\n", *line);
		if ((rc = fill_room_using_line(&room, *line)) == ERR || (rc == OK &&
		add_room_to_rooms(&rooms, &room, size, &place) == ERR))
			return (exit__(line, &rooms));
		ft_strdel(line);
	}
	*size = place;
	return (rooms);
}
