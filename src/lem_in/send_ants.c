/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 20:10:06 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/30 18:52:05 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	helper(t_lem_in *lem_in, size_t cur, t_list **way)
{
	size_t 	i;
	t_list			*lst;

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

static void	delete_ways(t_list ***ways, size_t size)
{
	size_t 	i;

	if (!ways || !*ways)
		return;
	i = -1;
	while (++i < size)
	{
		if (!(*ways)[i])
			break ;
		ft_lstdel_ic((*ways) + i);
	}
	ft_memdel((void **)ways);
}

static void show_way(t_lem_in *lem_in, t_list *way)
{
	t_list	*ptr;

	ptr = way;
	if (!ptr)
		return ;
	ft_printf("%s--", lem_in->rooms[ptr->content_size].name);
	while ((ptr = ptr->next))
		ft_printf("%s--", lem_in->rooms[ptr->content_size].name);
	ft_printf("\n");
}

static bool	step(t_lem_in *lem_in, int fdout)
{
	size_t 	i;
	bool			f;
	char			*name;

	f = 0;
	i = -1;
	name = NULL;
	while (++i < lem_in->ants_size)
	{
		if (lem_in->ants[i] && lem_in->ants[i] != (t_list *)-1)
		{
			if (lem_in->ants[i] == (t_list *)-2)
			{
				name = lem_in->rooms[1].name;
				lem_in->ants[i] = (t_list *)-1;
			}
			else
			{
				name = lem_in->rooms[lem_in->ants[i]->content_size].name;
				lem_in->ants[i] = (lem_in->ants[i]->next ?
				lem_in->ants[i]->next : (t_list *)-2);
			}
			ft_printf_fd(fdout, (f ? " L%zu-%s" : "L%zu-%s"), i, name);
			if (!f && name)
				f = true;
		}
	}
	if (f)
		ft_printf_fd(fdout, "\n");
	return (f);
}

int			send_ants(t_lem_in *lem_in, int fdout)
{
	t_list	**ways;
	size_t 	i;
	size_t 	k;
	size_t 	j;

	if (!(ways = ft_memalloc(sizeof(t_list *) * (lem_in->size - 1))))
		return (ERR);
	k = 0;
	i = -1;
	while (++i < lem_in->size)
		if (lem_in->flow[i * 2 + 1][2])
		{
			if (helper(lem_in, i, ways + k) == ERR)
			{
				delete_ways(&ways, lem_in->size - 1);
				return (ERR);
			}
			k++;
		}
	i = 0;
	while (i < lem_in->ants_size)
	{
		j = -1;
		while (++j < k && i < lem_in->ants_size)
			if (!lem_in->ants[i])
				lem_in->ants[i++] = ways[j];
		if (!step(lem_in, fdout))
		{
			delete_ways(&ways, lem_in->size - 1);
			return (OK);
		}
	}
	while (step(lem_in, fdout))
		;
	delete_ways(&ways, lem_in->size - 1);
	return (OK);
}
