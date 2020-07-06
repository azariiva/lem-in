/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ro_show.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 20:01:11 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/06 18:23:16 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libroom.h"
#include <stdio.h>

void	ro_show(t_room *room)
{
	if (!room)
		ft_printf("(null)");
	else
	{
		ft_printf("name: %s\ncoord: %d %d\visited: %d\n\n",
		room->name, room->coord.x, room->coord.y, room->visited);
	}
}
