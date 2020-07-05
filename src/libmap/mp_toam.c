/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_toam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 16:30:29 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/05 16:59:28 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmap.h"
#include <unistd.h>

t_am	*mp_toam(t_map *map)
{
	t_am	*am;
	t_list	*ptr;
	size_t	i;

	if (!(am = ft_memalloc(sizeof(t_am))))
	{
		ft_putendl_fd("Error: mp_toam allocation error", STDERR_FILENO);
		return (NULL);
	}
	am->ants = map->ants;
	am->size = ft_lstsize(map->middle) + 2;
	am->rooms = (t_room **)ft_memalloc(am->size);
	am->rooms[0] = map->start;
	am->rooms[am->size - 1] = map->end;
	i = 1;
	ptr = map->middle;
	while (i < am->size - 1)
	{
		am->rooms[i++] = *(t_room **)ptr->content;
		ptr = ptr->next;
	}
	am->edges = ft_memalloc(am->size * sizeof(int *))
}
