/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 19:14:49 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/18 19:18:05 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"

t_room		*new_room(char *name, int x, int y, t_room_type room_type)
{
	t_room	*new;

	if (!(new = ft_memalloc(sizeof(t_room))))
		return (NULL);
	if (!(new->name = ft_strdup(name)))
	{
		delete_room(&new);
		return (NULL);
	}
	new->room_type = room_type;
	new->x = x;
	new->y = y;
	return (new);
}
