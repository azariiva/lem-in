/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room_index.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhitmonc <lhitmonc@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 20:58:50 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/31 22:49:46 by lhitmonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"

static size_t	binary_search(t_room *rooms, size_t first, size_t last,
const char *name)
{
	size_t	mid;
	int		ret;

	if (first == last && ft_strcmp(rooms[first].name, name))
		return (-1);
	mid = first + (last - first) / 2;
	if ((ret = ft_strcmp(rooms[mid].name, name)) > 0)
		return (binary_search(rooms, first, mid - 1, name));
	else if (ret < 0)
		return (binary_search(rooms, mid + 1, last, name));
	return (mid);
}

size_t			get_room_index(t_room *rooms, size_t size, const char *name)
{
	if (rooms[0].name && !ft_strcmp(rooms[0].name, name))
		return (0);
	if (rooms[1].name && !ft_strcmp(rooms[1].name, name))
		return (1);
	return (binary_search(rooms, 2, size - 1, name));
}
