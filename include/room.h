/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 19:08:50 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/18 19:30:29 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef ROOM_H

# define ROOM_H

typedef enum	e_room_type
{
	R_MID = 0,
	R_END = 1,
	R_STR = 2
}				t_room_type;

typedef struct	s_room
{
	char		*name;
	t_room_type	room_type;
	int			x;
	int			y;
}				t_room;

/*
** Function new_room allocates memory and returns pointer to new room.
*/
t_room		*new_room(char *name, int x, int y, t_room_type room_type);

/*
** Function ro_del removes room and its name.
*/
void		delete_room(t_room **room);

/*
** Function atoroom use line and type to create new room using ro_new
** function.
*/
t_room		*atoroom(char *line, t_room_type room_type);

/*
** Function roomcmp checks if a and b have same names, same coordinates or same
** room_type differs from R_MID.
** Returns 0 if something wrong.
*/
int			roomcmp(t_room *a, t_room *b);

#endif
