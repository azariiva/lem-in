/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:33:34 by blinnea           #+#    #+#             */
/*   Updated: 2020/08/01 11:35:30 by blinnea          ###   ########.fr       */
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
		lem_in->rooms[i].load = (lem_in->rooms[i].old_load ?
		lem_in->rooms[i].old_load : 0);
}

static void	save_state(t_lem_in *lem_in)
{
	size_t register	i;

	i = -1;
	while (++i < lem_in->size)
	{
		lem_in->rooms[i].weight = 0;
		lem_in->rooms[i].old_load = (lem_in->rooms[i].load ?
		lem_in->rooms[i].load : 0);
		lem_in->rooms[i].load = 0;
	}
	lem_in->old_maxsteps = lem_in->maxsteps;
}

static void	remove_last_flow(t_lem_in *lem_in, char pv)
{
	size_t register	i;
	size_t register	j;

	i = 2;
	while (i != 1)
	{
		j = 0;
		while (++j < lem_in->size * 2)
			if (lem_in->path[j][i] == pv)
			{
				lem_in->flow[j][i] -= 1;
				lem_in->flow[i][j] += 1;
				i = j;
				break ;
			}
	}
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
		{
			remove_last_flow(lem_in, pv);
			break ;
		}
		save_state(lem_in);
	}
	reverse_state(lem_in);
	return (OK);
}
