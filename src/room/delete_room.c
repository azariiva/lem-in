/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 19:18:17 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/18 19:19:31 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"

void		delete_room(t_room **room)
{
	if (!room || !*room)
		return ;
	if ((*room)->name)
		ft_strdel(&((*room)->name));
	ft_memdel((void **)room);
}
