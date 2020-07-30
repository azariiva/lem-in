/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 20:35:06 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/30 18:38:05 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOM_H

# define ROOM_H

# include "libft.h"
# include <stdbool.h>

# ifndef RDSIZE
#  define RDSIZE 4
# endif

typedef struct	s_room
{
	char	*name;
	int		x;
	int		y;
	int		load;
	int		weight;
	int		old_load;
	int		old_weight;
}				t_room;

int				fill_room_using_line(t_room *room, char *line);
void			fill_room(t_room *room, const char *name, int x, int y);
void			roomcpy(t_room *dst, t_room *src);
int				add_room_to_rooms(t_room **rooms, t_room *room, size_t *size,
size_t *place);
t_room			*create_rooms(int fdin, int fdout, char **line, size_t *size);
void			delete_rooms(t_room **rooms, size_t size);
size_t			get_room_index(t_room *rooms, size_t size, const char *name);
void			sort_rooms(t_room *rooms, long long low, long long high);

#endif
