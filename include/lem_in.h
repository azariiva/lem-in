/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 20:39:37 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/31 21:22:22 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H

# define LEM_IN_H

# include "room.h"

typedef struct	s_lem_in
{
	t_room	*rooms;
	bool	*visited;

	int		ants_size;
	t_list	**ants;

	size_t	maxsteps;
	size_t	old_maxsteps;

	size_t	size;
	char	**flow;
	char	**old_flow;
	char	**capacity;
	char	**path;
	char	**residual_network;
}				t_lem_in;

int				fill_lem_in(t_lem_in *lem_in, int fdin, int fdout);
int				fill_graph(t_lem_in *lem_in, char **line, int fdin, int fdout);
void			delete_lem_in_content(t_lem_in *lem_in);

void			send_flow(t_lem_in *lem_in, char pv);
void			update_residual(t_lem_in *lem_in);
void			clear_visited(t_lem_in *lem_in);
int				find_path(t_lem_in *lem_in, char pv);
void			flowcpy(char **dst, char **src, size_t size);
int				edmonds_karp(t_lem_in *lem_in);
int				send_ants(t_lem_in *lem_in, int fdout);
void			measure_time(int fd, const char* name);
void			calc_load(t_lem_in *lem_in);
void			calc_weight(t_lem_in *lem_in);

#endif
