/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 18:32:15 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 03:56:43 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include <unistd.h>

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
	am->rooms[0]->visited = 1;
	queue = ft_quenew(NULL, 0);
	// ft_printf("____find_shortest____\n");
	while (!ft_queisempty(queue) && !am->rooms[am->size - 1]->visited)
	{
		flag = 1;
		v = ft_quepop(queue);
		idx = -1;
		while (++idx < am->size)
		{
			if (am->edges[v->content_size][idx] &&
				am->flow[v->content_size][idx] == -1 &&
				!am->rooms[idx]->visited)
			{
				// ft_printf("%zu(%d)-(-1)->%zu(%d)\n", v->content_size, am->rooms[v->content_size]->weight, idx, am->rooms[idx]->weight);
				if (am->rooms[v->content_size]->weight - 1 < am->rooms[idx]->weight)
				{
					// ft_printf("before:\n");
					// am_show_flow(am);
					am_removeflow(am, idx);
					// ft_printf("after:\n");
					// am_show_flow(am);
					// ft_printf("\n");
				}
				am->rooms[idx]->weight = am->rooms[v->content_size]->weight - 1;
				am->rooms[idx]->visited = 1;
				am->addgraph[v->content_size][idx] = 1;
				am->addgraph[idx][v->content_size] = -1;
				flag = 0;
				ft_queadd(queue, ft_lstnew_ic(idx));
			}
		}
		if (flag)
		{
			idx = -1;
			while (++idx < am->size)
			{
				if (am->edges[v->content_size][idx] &&
					!am->flow[v->content_size][idx] &&
					!am->rooms[idx]->visited)
				{
					// ft_printf("%zu(%d)-(+1)->%zu(%d)\n", v->content_size, am->rooms[v->content_size]->weight, idx, am->rooms[idx]->weight);
					if (am->rooms[v->content_size]->weight + 1 < am->rooms[idx]->weight)
					{
						// ft_printf("before:\n");
						// am_show_flow(am);
						am_removeflow(am, idx);
						// ft_printf("after:\n");
						// am_show_flow(am);
						// ft_printf("\n");
					}
					am->rooms[idx]->weight = am->rooms[v->content_size]->weight + 1;
					am->rooms[idx]->visited = 1;
					am->addgraph[v->content_size][idx] = 1;
					am->addgraph[idx][v->content_size] = -1;
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
				break ;
			}
		}
	}
	// ft_printf("flow:\n");
	// am_show_flow(am);
	// ft_printf("------------------------------------------------------------\n");

	return (OK);
}
