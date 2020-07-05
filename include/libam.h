/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libam.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 16:06:34 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/05 17:48:29 by blinnea          ###   ########.fr       */
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
	int		**resedges;
}				t_am;

t_am	*am_new(int fd);
void	am_del(t_am **am);

#endif
