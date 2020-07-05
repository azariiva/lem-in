/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ro_show.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 20:01:11 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/02 15:02:29 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libroom.h"
#include <stdio.h>

void	ro_show(t_room *room)
{
	t_list	*ptr;

	if (!room)
		ft_putendl("(null)");
	else
	{
		printf("name: %s\ncoord: %d %d\nweight: %d\n",
		room->name, room->coord.x, room->coord.y, room->weight);
		ft_putendl("Links:");
		ptr = room->links;
		while (ptr)
		{
			if ((*(t_room **)ptr->content)->name)
				ft_putendl((*(t_room **)ptr->content)->name);
			else
				ft_putendl("(null)");
			ptr = ptr->next;
		}
		ft_putendl("\n");
	}
}
