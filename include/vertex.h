/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 19:39:09 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/18 20:30:10 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEX_H

# define VERTEX_H

# include "room.h"
# include "edge.h"

typedef struct	s_edge	t_edge;

typedef struct			s_vertex
{
	t_room	*room;
	t_queue	*edges;
}						t_vertex;

t_vertex				*new_vertex(t_room *room);
void					delete_vertex(t_vertex **vertex);
/*
** Returns ERR if edge is already present in vertex->edges
*/
int						add_edge_to_vertex(t_vertex *vertex, t_edge *edge);

#endif
