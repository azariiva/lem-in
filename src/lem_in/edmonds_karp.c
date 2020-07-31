/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:33:34 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/31 15:57:38 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <sys/time.h>

static void	reverse_state(t_lem_in *lem_in)
{
	size_t	i;

	i = -1;
	lem_in->maxsteps = lem_in->old_maxsteps;
	while (++i < lem_in->size)
	{
		lem_in->rooms[i].weight = lem_in->rooms[i].old_weight;
		lem_in->rooms[i].load = lem_in->rooms[i].old_load;
	}
	flowcpy(lem_in->flow, lem_in->old_flow, lem_in->size);
}

static void	save_state(t_lem_in *lem_in)
{
	size_t 	i;

	i = 0;
	lem_in->old_maxsteps = lem_in->maxsteps;
	while (i < lem_in->size)
	{
		if (lem_in->rooms[i].weight)
		{
			lem_in->rooms[i].old_weight = lem_in->rooms[i].weight;
			lem_in->rooms[i].weight = 0;
		}
		if (lem_in->rooms[i].load)
		{
			lem_in->rooms[i].old_load = lem_in->rooms[i].load;
			lem_in->rooms[i].load = 0;
		}
		i++;
	}
	flowcpy(lem_in->old_flow, lem_in->flow, lem_in->size);
}

static void	calc_load(t_lem_in *lem_in)
{
	size_t			ants_left;
	size_t 	i;
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
			if (room && lem_in->flow[1][i * 2] == 1 && lem_in->rooms[i].weight + lem_in->rooms[i].load < room->weight + room->load)
				room = lem_in->rooms + i;
		}
		if ((size_t)(++room->load + room->weight) > lem_in->maxsteps)
			lem_in->maxsteps = room->load + room->weight;
		ants_left--;
	}

}

static void	helper(t_lem_in *lem_in, size_t cur)
{
	size_t 	i;

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
				break;
			}
		}
	}
}

static void	calc_weight(t_lem_in *lem_in)
{
	size_t 	i;

	i = -1;
	while (++i < lem_in->size)
		if (lem_in->flow[i * 2 + 1][2])
			helper(lem_in, i);
}

int			edmonds_karp(t_lem_in *lem_in)
{
	char	pv;

	pv = 1;
	if (find_path(lem_in, pv) != OK)
		return (ERR);
	send_flow(lem_in, pv);
	calc_weight(lem_in);
	calc_load(lem_in);
	save_state(lem_in);
	while (find_path(lem_in, ++pv) == OK)
	{
		send_flow(lem_in, pv);
		calc_weight(lem_in);
		calc_load(lem_in);
		if (lem_in->maxsteps >= lem_in->old_maxsteps)
			break ;
		save_state(lem_in);
	}
	reverse_state(lem_in);
	return (OK);
}
