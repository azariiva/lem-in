/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_edge_to_vertex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 19:55:42 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/18 20:30:56 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vertex.h"

static int	check_edges(t_queue *edges, t_edge *edge)
{
	t_list	*ptr;

	ptr = edges->head;
	while (ptr)
	{
		if (!edgecmp(*(t_edge **)ptr->content , edge))
			return (0);
		ptr = ptr->next;
	}
	return (0);
}

int			add_edge_to_vertex(t_vertex *vertex, t_edge *edge)
{
	t_queue	*edges;


}
