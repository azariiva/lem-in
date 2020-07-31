/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:33:34 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/31 22:10:42 by blinnea          ###   ########.fr       */
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
		lem_in->rooms[i].weight = (lem_in->rooms[i].old_weight ?
		lem_in->rooms[i].old_weight : 0);
		lem_in->rooms[i].load = (lem_in->rooms[i].old_load ?
		lem_in->rooms[i].old_load : 0);
	}
	flowcpy(lem_in->flow, lem_in->old_flow, lem_in->size);
}

static void	save_state(t_lem_in *lem_in)
{
	size_t register	i;

	i = -1;
	while (++i < lem_in->size)
	{
		lem_in->rooms[i].old_weight = (lem_in->rooms[i].weight ?
		lem_in->rooms[i].weight : 0);
		lem_in->rooms[i].weight = 0;
		lem_in->rooms[i].old_load = (lem_in->rooms[i].load ?
		lem_in->rooms[i].load : 0);
		lem_in->rooms[i].load = 0;
	}
	lem_in->old_maxsteps = lem_in->maxsteps;
	flowcpy(lem_in->old_flow, lem_in->flow, lem_in->size);
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
		if (lem_in->maxsteps > lem_in->old_maxsteps)
			break ;
		save_state(lem_in);
	}
	reverse_state(lem_in);
	return (OK);
}
