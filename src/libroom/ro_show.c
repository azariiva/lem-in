/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ro_show.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 20:01:11 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 05:42:55 by blinnea          ###   ########.fr       */
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
		ft_printf("name: %s\ncoord: %d %d\v: %d\n\n",
		room->name, room->c.x, room->c.y, room->v);
	}
}
