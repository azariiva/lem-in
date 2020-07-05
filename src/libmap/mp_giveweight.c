/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_giveweight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:31:19 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/05 16:31:06 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmap.h"
#include "libft_memory.h"
#include <limits.h>

static void	del(void *content, size_t size)
{
	if (size)
		ft_memdel(&content);
}

void		mp_giveweight(t_map *map)
{
	t_queue	*queue;
	t_list	*u;
	t_list	*v;

	map->start->weight = 0;
	queue = ft_quenew(&(map->start), sizeof(t_room *));
	while (!ft_queisempty(queue))
	{
		u = ft_quepop(queue);
		v = (*(t_room **)u->content)->links;
		while (v)
		{
			if ((*(t_room **)v->content)->weight == INT_MAX && (*(t_room **)v->content) != map->end)
			{
				(*(t_room **)v->content)->weight = (*(t_room **)u->content)->weight + 1;
				ft_queadd(queue, ft_lstnew((void *)(t_room **)v->content, sizeof(t_room *)));
			}
			v = v->next;
		}
		ft_lstdelone(&u, del);
	}
	ft_quedel(&queue, del);
}
