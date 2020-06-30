/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_show.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:48:33 by blinnea           #+#    #+#             */
/*   Updated: 2020/06/30 20:02:05 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmap.h"

void		mp_show(t_map *map)
{
	t_list	*ptr;

	ft_putendl("##start");
	ro_show(map->start);
	ptr = map->middle;
	while (ptr)
	{
		ro_show(*(t_room **)ptr->content);
		ptr = ptr->next;
	}
	ft_putendl("##end");
	ro_show(map->end);
}
