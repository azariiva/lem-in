/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 04:07:24 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 04:03:53 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "libway.h"
#include <unistd.h>

static void	spread_ants(t_ant *ants, size_t q, t_way *ways)
{
	size_t	i;
	t_way	*chosen;
	t_way	*ptr;

	i = -1;
	while (++i < q)
	{
		chosen = ways;
		ptr = ways + 1;
		while (ptr->len)
		{
			if (chosen->ants + chosen->len > ptr->ants + ptr->len)
				chosen = ptr;
			++ptr;
		}
		ants[i].way = chosen;
		chosen->ants++;
	}
}

static void	i_hate_norminette(t_am *am, t_ant *ants)
{
	int	flag;
	int	i;

	flag = 1;
	while (flag && (i = -1))
	{
		flag = 0;
		while (++i < am->ants)
		{
			if (ants[i].cur_node != ants[i].way->len - 1 &&
				!am->rooms[ants[i].way->nodes[ants[i].cur_node + 1]]->visited)
			{
				am->rooms[ants[i].way->nodes[ants[i].cur_node]]->visited = 0;
				ants[i].cur_node++;
				(flag ? ft_printf(" ") : 0);
				flag = 1;
				ft_printf("L%zu-%s", i + 1, am->rooms[ants[i].way->nodes[ants[i].cur_node]]->name);
				if (ants[i].cur_node != ants[i].way->len - 1)
					am->rooms[ants[i].way->nodes[ants[i].cur_node]]->visited = 1;
			}
		}
		(flag ? ft_printf("\n") : 0);
	}
}

int			run_ants(t_am *am)
{
	t_ant		*ants;
	t_way		*ways;

	if (!(ants = ft_memalloc(am->ants * sizeof(t_ant))))
		return (ERR);
	if (!(ways = way_find_all(am)))
	{
		ft_memdel((void **)ants);
		return (ERR);
	}
	spread_ants(ants, am->ants, ways);
	am_clear_visited(am);
	i_hate_norminette(am, ants);
	ft_memdel((void **)&ants);
	way_del(&ways);
	return (OK);
}
