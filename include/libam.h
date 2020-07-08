/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libam.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 16:06:34 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/08 16:08:52 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBAM_H

# define LIBAM_H

#include "libroom.h"

typedef struct	s_am
{
	int		ants;
	size_t	size;
	t_room	**rooms;
	int		**edges;
	int		**flow;
	int		**addgraph;
}				t_am;

t_am	*am_new(int fd);
void	am_del(t_am **am);
size_t	am_str_to_idx(char *str, t_am *am);
int		am_addlink(char *line, t_am *am);
void	am_show(t_am *am);
void	am_clear_visited(t_am *am);
void	am_clear_addgraph(t_am *am);
void	am_show_addgraph(t_am *am);
void	am_removeflow(t_am *am, size_t v);
void	am_show_flow(t_am *am);

#endif
