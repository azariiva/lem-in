/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:08:59 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/01 22:47:39 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmap.h"
#include "libft_memory.h"

static void	del(void *content, size_t size)
{
	if (size)
	{
		ro_free((t_room **)content);
		ft_memdel(&content);
	}
}

void		mp_free(t_map **map)
{
	ft_lstdel(&((*map)->middle), del);
	if ((*map)->start != (*map)->end)
		ro_free(&((*map)->start));
	(*map)->start = NULL;
	ro_free(&((*map)->end));
	ft_memdel((void **)map);
}
