/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_edge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 20:00:16 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/18 20:22:57 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edge.h"

t_edge	*new_edge(t_vertex *source, t_vertex *sink, int capacity)
{
	t_edge	*new;

	if (!(new = ft_memalloc(sizeof(t_edge))))
		return (NULL);
	new->capacity = capacity;
	new->source = source;
	new->sink = sink;
	new->flow = 0;
}
