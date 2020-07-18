/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_vertex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 19:46:08 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/18 19:50:28 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vertex.h"

t_vertex	*new_vertex(t_room *room)
{
	t_vertex	*new;

	if (!(new = ft_memalloc(sizeof(t_vertex))))
		return (NULL);
	if (!(new->edges = ft_memalloc(sizeof(t_queue))))
	{
		delete_vertex(&new);
		return (NULL);
	}
	new->room = room;
	return (new);
}
