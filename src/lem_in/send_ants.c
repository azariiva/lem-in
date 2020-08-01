/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 20:10:06 by blinnea           #+#    #+#             */
/*   Updated: 2020/08/01 12:39:00 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <unistd.h>

static void	helper_step(t_lem_in *lem_in, char **name, int register i)
{
	if (lem_in->ants[i] == (t_list *)-2)
	{
		*name = lem_in->rooms[1].name;
		lem_in->ants[i] = (t_list *)-1;
	}
	else
	{
		*name = lem_in->rooms[lem_in->ants[i]->content_size].name;
		lem_in->ants[i] = (lem_in->ants[i]->next ?
		lem_in->ants[i]->next : (t_list *)-2);
	}
}

static bool	step(t_lem_in *lem_in, int fdout)
{
	int register	i;
	bool			f;
	char			*name;

	f = 0;
	i = -1;
	name = NULL;
	while (++i < lem_in->ants_size)
	{
		if (lem_in->ants[i] && lem_in->ants[i] != (t_list *)-1)
		{
			helper_step(lem_in, &name, i);
			ft_printf_fd(fdout, (f ? " L%zu-%s" : "L%zu-%s"), i + 1, name);
			if (!f && name)
				f = true;
		}
	}
	if (f)
		ft_printf_fd(fdout, "\n");
	return (f);
}

void		helper_send_ants(t_lem_in *lem_in, size_t *i,
								size_t *j, t_list ***ways)
{
	if (!lem_in->ants[*i] && lem_in->rooms[(*ways)[*j]->content_size].load)
	{
		lem_in->rooms[(*ways)[*j]->content_size].load--;
		lem_in->ants[(*i)++] = (*ways)[*j];
	}
}

int			send_ants(t_lem_in *lem_in, int fdout)
{
	t_list			**ways;
	size_t			i;
	size_t			j;

	if (!(ways = new_ways(lem_in)))
		return (ERR);
	ft_printf_fd(fdout, "\n");
	i = 0;
	while (i < (size_t)lem_in->ants_size)
	{
		j = -1;
		while (ways[++j] && i < (size_t)lem_in->ants_size)
			helper_send_ants(lem_in, &i, &j, &ways);
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
