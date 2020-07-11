/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libam.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 16:06:34 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 06:42:24 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBAM_H

# define LIBAM_H

# include "libroom.h"

# ifndef E_ECHO_CMD

#  define E_ECHO_CMD

enum			e_echo_cmd
{
	EC_ADD = 1,
	EC_SHOW = 2,
	EC_DEL = 3
};

# endif

typedef struct	s_am
{
	int		ants;
	size_t	size;
	t_room	**r;
	int		**e;
	int		**f;
	int		**a;
}				t_am;

t_am			*am_new(int fd);
void			am_del(t_am **am);
size_t			am_str_to_idx(char *str, t_am *am);
int				am_addlink(char *line, t_am *am);

void			am_show(t_am *am);
void			am_clear_av(t_am *am);

void			am_show_addgraph(t_am *am);
void			am_rmf(t_am *am, size_t v);
void			am_show_flow(t_am *am);
int				am_gnl(int fd, char **line);
int				am_addrooms(t_am *am, t_list *r, t_room *start, t_room *end);
void			del(void *content, size_t size);
int				am_read_room(char *line, t_list **r, t_room **ser);

#endif
