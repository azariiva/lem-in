/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:08:59 by blinnea           #+#    #+#             */
/*   Updated: 2020/06/30 00:57:38 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmap.h"

static void	del(void *content, size_t size)
{
	if (size && content != NULL)
	{
		ro_free((t_room **)content);
		free(content);
	}
}

void		mp_free(t_map **map)
{
	ft_lstdel(&((*map)->middle), del);
	if ((*map)->start != (*map)->end)
		ro_free(&((*map)->start));
	(*map)->start = NULL;
	ro_free(&((*map)->end));
	free(*map);
	*map = NULL;
}
