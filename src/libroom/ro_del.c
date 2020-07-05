/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ro_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:03:22 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/05 17:51:12 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libroom.h"

void		ro_del(t_room **room)
{
	if (room == NULL || *room == NULL)
		return ;
	if ((*room)->name != NULL)
		ft_strdel(&((*room)->name));
	ft_memdel((void **)room);
}
