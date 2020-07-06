/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 18:32:15 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/06 21:57:14 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

static void	del(void *content, size_t size)
{
	if (content && size)
		ft_memdel(&content);
}

int		find_shortest(t_am *am)
{
	t_queue		*queue;
	t_list		*v;
	size_t		idx;
	size_t		current;
	int			flag;

	am_clear_addgraph(am);
	am_clear_visited(am);
	queue = ft_quenew(NULL, 0);
	while (!ft_queisempty(queue) && !am->rooms[am->size - 1]->visited)
	{
		flag = 1;
		v = ft_quepop(queue);
		am->rooms[v->content_size]->visited = 1;
		idx = -1;
		while (++idx < am->size)
		{
			if (am->edges[v->content_size][idx] &&
				am->flow[v->content_size][idx] == -1 &&
				!am->rooms[idx]->visited)
			{
				// if (am->rooms[v->content_size]->weight - 1 < am->rooms[idx]->weight)
				// 	am_removeflow(am, idx);
				am->addgraph[v->content_size][idx] = 1;
				am->addgraph[idx][v->content_size] = -1;
				am->rooms[idx]->weight = am->rooms[v->content_size]->weight - 1;
				flag = 0;
				ft_queadd(queue, ft_lstnew_ic(idx));
			}
		}
		if (flag)
		{
			idx = -1;
			while (++idx < am->size)
			{
				if (am->edges[v->content_size][idx] && am->flow[v->content_size][idx] != 1 && !am->rooms[idx]->visited)
				{
					// if (am->rooms[v->content_size]->weight + 1 < am->rooms[idx]->weight)
					// 	am_removeflow(am, idx);
					am->addgraph[v->content_size][idx] = 1;
					am->addgraph[idx][v->content_size] = -1;
					am->rooms[idx]->weight = am->rooms[v->content_size]->weight + 1;
					if (idx == am->size - 1)
					{
						am->rooms[am->size - 1]->visited = 1;
						break;
					}
					ft_queadd(queue, ft_lstnew_ic(idx));
				}
			}
		}
		ft_lstdelone_ic(&v);
	}
	ft_quedel(&queue, del);
	if (!am->rooms[am->size - 1]->visited)
		return (END);
	current = am->size - 1;
	while (current != 0)
	{
		idx = -1;
		while (++idx < am->size)
		{
			if (am->addgraph[current][idx] == -1)
			{
				am->flow[current][idx] -= 1;
				am->flow[idx][current] += 1;
				current = idx;
				break;
			}
		}
	}
	return (OK);
}
