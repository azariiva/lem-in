/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 12:34:07 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/31 21:23:08 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <sys/time.h>

static int	exit__(t_queue **q, int rc)
{
	if (q)
		ft_quedel(q, NULL);
	return (rc);
}

static int	loop__(t_lem_in *lem_in, t_queue *q, char pv)
{
	t_list			*l;
	size_t register	i;
	size_t register	cur;

	l = ft_quepop(q);
	cur = l->content_size;
	ft_lstdelone_ic(&l);
	i = 1;
	while (++i < lem_in->size * 2)
	{
		if (lem_in->residual_network[cur][i] && !lem_in->visited[i])
		{
			lem_in->path[cur][i] = pv;
			if (!(l = ft_lstnew_ic(i)))
				return (ERR);
			ft_queadd(q, l);
			lem_in->visited[i] = true;
		}
	}
	return (OK);
}

int			find_path(t_lem_in *lem_in, char pv)
{
	t_queue			*q;
	t_list			*l;

	ft_bzero(lem_in->visited, lem_in->size * 2 * sizeof(bool));
	if (!(q = ft_memalloc(sizeof(t_queue))))
		return (ERR);
	if (!(l = ft_lstnew_ic(1)))
		return (exit__(&q, ERR));
	ft_queadd(q, l);
	lem_in->visited[0] = true;
	lem_in->visited[1] = true;
	while (!ft_queisempty(q) && !lem_in->visited[2])
		if (loop__(lem_in, q, pv) == ERR)
			return (exit__(&q, ERR));
	if (!lem_in->visited[2])
		return (exit__(&q, END));
	return (exit__(&q, OK));
}
