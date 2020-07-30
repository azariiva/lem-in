/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 20:38:36 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/28 19:05:02 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"

void	roomcpy(t_room *dst, t_room *src)
{
	size_t	ignore;

	ignore = sizeof(int) * 4;
	ft_memcpy(dst, src, sizeof(t_room) - ignore);
}

void	fill_room(t_room *room, const char *name, int x, int y)
{
	room->name = ft_strdup(name);
	room->x = x;
	room->y = y;
}
