/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_find.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:56:33 by blinnea           #+#    #+#             */
/*   Updated: 2020/06/30 01:07:28 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmap.h"

t_room	*mp_find(t_map *map, char *name)
{
	t_list	*ptr;

	if (!ft_strcmp(map->start->name, name))
		return (map->start);
	if (!ft_strcmp(map->end->name, name))
		return (map->end);
	ptr = map->middle;
	while (ptr)
	{
		if (!ft_strcmp(((*(t_room **)ptr->content))->name, name))
			return (*(t_room **)ptr->content);
		ptr = ptr->next;
	}
	return (NULL);
}
