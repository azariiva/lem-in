/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 23:08:50 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/30 18:52:05 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"

void	delete_rooms(t_room **rooms, size_t size)
{
	size_t 	i;

	i = -1;
	while (++i < size)
		ft_strdel(&((*rooms + i)->name));
	ft_memdel((void **)rooms);
}
