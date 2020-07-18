/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 19:40:52 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/18 20:28:10 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDGE_H

# define EDGE_H

# include "vertex.h"

typedef struct	s_vertex	t_vertex;

typedef struct 				s_edge
{
	t_vertex	*source;
	t_vertex	*sink;
	int			flow;
	int			capacity;
}							t_edge;

t_edge						*new_edge(t_vertex *source, t_vertex *sink,
int capacity);
void						delete_edge(t_edge **edge);
/*
** Function edgecmp checks if a and b have the same source and sink.
** Returns 0 if something wrong.
*/
int							edgecmp(t_edge *a, t_edge *b);

#endif
