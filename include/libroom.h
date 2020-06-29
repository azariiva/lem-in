/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libroom.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 23:13:37 by blinnea           #+#    #+#             */
/*   Updated: 2020/06/29 17:14:23 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOM_H

# define ROOM_H

# ifndef E_RCODE

#  define E_RCODE

enum
{
	ERR = -1,
	OK = 1,
	END = 0
};

# endif

# include "libft.h"
# include "libcoord.h"

typedef enum	e_linktype
{
	SINGLE_LINK = 1,
	DOUBLE_LINK = 2
}				t_linktype;

typedef struct	s_room
{
	char	*name;
	t_coord	coord;
	t_list	*links;
}				t_room;

/*
** Function ro_new allocates memory and returns pointer to new room.
*/
t_room		*ro_new(char *name, t_coord coord);

/*
** Function ro_atoroom use line and type to create new room using ro_new
** function.
*/
t_room		*ro_atoroom(char *line);

/*
** Function ro_free removes room and all its links.
*/
void		ro_free(t_room **room);

/*
** Function ro_connect adds links with each other to rooms a and b.
*/
int			ro_connect(t_room *a, t_room *b, t_linktype linktype);

/*
** Function ro_compare checks if a and b have same names or same coordinates.
*/
int			ro_compare(t_room *a, t_room *b);

#endif
