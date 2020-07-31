/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhitmonc <lhitmonc@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 22:25:33 by lhitmonc          #+#    #+#             */
/*   Updated: 2020/07/31 22:33:53 by lhitmonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		delete_ways(t_list ***ways, size_t size)
{
	size_t	i;

	if (!ways || !*ways)
		return ;
	i = -1;
	while (++i < size)
	{
		if (!(*ways)[i])
			break ;
		ft_lstdel_ic((*ways) + i);
	}
	ft_memdel((void **)ways);
}

static int	helper(t_lem_in *lem_in, size_t cur, t_list **way)
{
	size_t	i;
	t_list	*lst;

	if (!(*way = ft_lstnew_ic(cur)))
		return (ERR);
	while (!lem_in->flow[1][cur * 2])
	{
		i = 0;
		while (++i < lem_in->size)
		{
			if (lem_in->flow[i * 2 + 1][cur * 2] == 1)
			{
				if (!(lst = ft_lstnew_ic(i)))
					return (ERR);
				ft_lstadd(way, lst);
				cur = i;
				break ;
			}
		}
	}
	return (OK);
}

t_list		**new_ways(t_lem_in *lem_in)
{
	t_list	**ways;
	size_t	i;
	size_t	k;

	if (!(ways = ft_memalloc(sizeof(t_list *) * (lem_in->size - 1))))
		return (NULL);
	k = 0;
	i = 0;
	while (++i < lem_in->size)
		if (lem_in->flow[i * 2 + 1][2])
		{
			if (helper(lem_in, i, ways + k) == ERR)
			{
				delete_ways(&ways, lem_in->size - 1);
				return (NULL);
			}
			k++;
		}
	return (ways);
}
