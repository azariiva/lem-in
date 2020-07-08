/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_find_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 04:31:04 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/08 18:20:13 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libway.h"
#include <unistd.h>

static size_t	find_waylen(size_t v, t_am *am)
{
	size_t	ctr;
	size_t	i;

	ctr = 0;
	while (v != am->size - 1)
	{
		ctr++;
		i = -1;
		while (++i < am->size)
		{
			if (am->flow[v][i] == 1)
			{
				v = i;
				break;
			}
		}
	}
	return (ctr);
}

static int		add_way(size_t v, t_way *way, t_am *am)
{
	size_t	i;
	size_t	j;

	way->len = find_waylen(v, am) + 2;
	if (!(way->nodes = ft_memalloc(way->len * sizeof(size_t))))
	{
		ft_printf_fd(STDERR_FILENO, "{red}Error:{eoc} allocation error.\n");
		return (ERR);
	}
	way->nodes[0] = 0;
	if (way->len > 2)
		way->nodes[1] = v;
	way->nodes[way->len - 1] = am->size - 1;
	i = 1;
	while (++i < way->len - 1)
	{
		j = -1;
		while (++j < am->size)
		{
			if (am->flow[v][j] == 1)
			{
				way->nodes[i] = j;
				v = j;
				break;
			}
		}
	}
	return (OK);
}

t_way			*way_find_all(t_am *am)
{
	t_way	*ways;
	size_t	wc;
	size_t	i;
	size_t	j;

	wc = way_count(am);
	if (!(ways = ft_memalloc((wc + 1) * sizeof(t_way))))
	{
		ft_printf_fd(STDERR_FILENO, "{red}Error:{eoc} allocation error.\n");
		return (NULL);
	}
	i = -1;
	j = 0;
	while (++i < am->size)
	{
		if (am->flow[0][i] == 1 && add_way(i, ways + j++, am) == ERR)
		{
			way_del(&ways);
			break;
		}
	}
	return (ways);
}
