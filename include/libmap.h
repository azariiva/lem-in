/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:45:27 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/05 17:29:56 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMAP_H

# define LIBMAP_H

# include "libam.h"
# include "libft_queue.h"
# include "libroom.h"

# ifndef E_RTYPE

#  define E_RTYPE

typedef enum	e_rtype
{
	MIDDLE_ROOM = 0,
	START_ROOM = 1,
	END_ROOM = 2
}				t_rtype;

# endif

typedef struct	s_map
{
	int		ants;
	t_room	*start;
	t_room	*end;
	t_list	*middle;
}				t_map;

/*
** Function mp_new creates new map using data that comes from file descriptor\
** fd as a source.
*/
t_map	*mp_new(int fd);

/*
** Function mp_add adds room to structure map.
*/
int		mp_add(t_map *map, t_room *room, t_rtype rtype);


/*
** Function mp_free removes map and all it's links.
*/
void	mp_free(t_map **map);

/*
** Function mp_find searches for a room which has the name.
** mp_find returns room on success, NULL on failure.
*/
t_room	*mp_find(t_map *map, char *name);

/*
** Function mp_atolink creates link between two rooms based on line.
*/
int		mp_atolink(t_map *map, char *line);

void	mp_giveweight(t_map *map);

void	mp_show(t_map *map);

t_am	*mp_toam(t_map *map);

#endif
