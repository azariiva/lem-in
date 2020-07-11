/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 18:32:15 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 06:45:22 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include <unistd.h>

static void		idfk1(t_am *am, t_list *v, t_queue *q, size_t i)
{
	(am->r[v->size]->w - 1 < am->r[i]->w ? am_rmf(am, i) : 0);
	am->r[i]->v = 1;
	am->a[v->size][i] = 1;
	am->a[i][v->size] = -1;
	am->r[i]->w = am->r[v->size]->w - 1;
	ft_queadd(q, ft_lstnew_ic(i));
}

static void		idfk2(t_am *am, t_list *v, t_queue *q, size_t i)
{
	(am->r[v->size]->w + 1 < am->r[i]->w ? am_rmf(am, i) : 0);
	am->r[i]->v = 1;
	am->a[v->size][i] = 1;
	am->a[i][v->size] = -1;
	am->r[i]->w = am->r[v->size]->w + 1;
	ft_queadd(q, ft_lstnew_ic(i));
}

static int		life_sucks(t_am *am, t_queue **q)
{
	size_t	i;
	size_t	j;

	ft_quedel(q, del);
	if (!am->r[am->size - 1]->v)
		return (END);
	j = am->size - 1;
	while (j && (i = -1))
		while (++i < am->size)
			if (am->a[j][i] == -1)
			{
				am->f[j][i] -= 1;
				am->f[i][j] += 1;
				j = i;
				break ;
			}
	return (OK);
}

int				find_shortest(t_am *am)
{
	t_queue		*q;
	t_list		*v;
	size_t		i;
	int			f;

	am_clear_av(am);
	am->r[0]->v = 1;
	if (!(q = ft_quenew(NULL, 0)))
		return (ERR);
	v = NULL;
	while ((f = 1) && !ft_queisempty(q) && !am->r[am->size - 1]->v)
	{
		v = ft_quepop(q);
		i = -1;
		while (++i < am->size)
			if (am->e[v->size][i] && am->f[v->size][i] == -1 && !am->r[i]->v &&
			!(f = 0))
				idfk1(am, v, q, i);
		if (f && (i = -1))
			while (++i < am->size)
				if (am->e[v->size][i] && !am->f[v->size][i] && !am->r[i]->v)
					idfk2(am, v, q, i);
		ft_lstdelone_ic(&v);
	}
	return (life_sucks(am, &q));
}
