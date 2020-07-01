/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ro_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:03:22 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/01 22:46:56 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libroom.h"

static void	del(void *content, size_t size)
{
	if (size)
		ft_memdel(&content);
}

void		ro_free(t_room **room)
{
	if (room == NULL || *room == NULL)
		return ;
	if ((*room)->name != NULL)
		ft_strdel(&((*room)->name));
	ft_lstdel(&((*room)->links), del);
	ft_memdel((void **)room);
}
