/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libway.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 04:21:41 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 03:52:11 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBWAY_H

# define LIBWAY_H

# include "libam.h"

typedef struct	s_way
{
	size_t	len;
	size_t	ants;
	size_t	*nodes;
}				t_way;

typedef struct	s_ant
{
	t_way	*way;
	size_t	cur_node;
}				t_ant;

void			way_del(t_way **way);
t_way			*way_find_all(t_am *am);
size_t			way_count(t_am *am);
void			way_show(t_way *way, t_room **rooms);

#endif
