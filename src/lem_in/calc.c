/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 21:21:05 by blinnea           #+#    #+#             */
/*   Updated: 2020/08/01 11:35:38 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		calc_load(t_lem_in *lem_in)
{
	size_t			ants_left;
	size_t register	i;
	t_room			*room;

	lem_in->maxsteps = 0;
	ants_left = lem_in->ants_size;
	while (ants_left)
	{
		i = 0;
		room = NULL;
		while (++i < lem_in->size)
		{
			if (lem_in->rooms[i].weight && lem_in->flow[1][i * 2] == 1 && !room)
				room = lem_in->rooms + i;
			else if (room && lem_in->flow[1][i * 2] == 1 &&
			lem_in->rooms[i].weight + lem_in->rooms[i].load <
			room->weight + room->load)
				room = lem_in->rooms + i;
		}
		if ((size_t)(++room->load + room->weight) > lem_in->maxsteps)
			lem_in->maxsteps = room->load + room->weight;
		ants_left--;
	}
}

static void	helper(t_lem_in *lem_in, size_t cur)
{
	size_t register	i;

	lem_in->rooms[cur].weight = 1;
	while (!lem_in->flow[1][cur * 2])
	{
		i = 0;
		while (++i < lem_in->size)
		{
			if (lem_in->flow[i * 2 + 1][cur * 2] == 1)
			{
				lem_in->rooms[i].weight = lem_in->rooms[cur].weight + 1;
				cur = i;
				break ;
			}
		}
	}
}

void		calc_weight(t_lem_in *lem_in)
{
	size_t register	i;

	i = -1;
	while (++i < lem_in->size)
		if (lem_in->flow[i * 2 + 1][2])
			helper(lem_in, i);
}
