/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 17:14:53 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 06:43:24 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libam.h"
#include <unistd.h>

static void	full_del(void *content, size_t size)
{
	if (content && size)
	{
		ro_del((t_room **)content);
		ft_memdel(&content);
	}
}

static t_am	*err(t_room **ser, t_am **am, t_list **r)
{
	if (ser)
	{
		ro_del(ser);
		ro_del(ser + 1);
	}
	am_del(am);
	ft_lstdel(r, full_del);
	am_gnl(-1, NULL);
	return (NULL);
}

static t_am	*read_links(t_am **am, char *line, int fd)
{
	int	rc;

	rc = OK;
	while (rc == OK)
	{
		if (am_addlink(line, *am) == ERR)
			return (err(NULL, am, NULL));
		if ((rc = am_gnl(fd, &line)) == ERR)
			return (err(NULL, am, NULL));
	}
	am_gnl(-1, NULL);
	return (*am);
}

t_am		*am_new(int fd)
{
	t_am	*am;
	t_list	*r;
	t_room	*ser[2];
	char	*line;

	ser[0] = NULL;
	ser[1] = NULL;
	r = NULL;
	if (!(am = ft_memalloc(sizeof(t_am))))
		return (NULL);
	am_gnl(fd, &line);
	if ((am->ants = ft_atoi(line)) <= 0)
		return (err(NULL, &am, NULL));
	while (am_gnl(fd, &line) == OK && !ft_strchr(line, '-'))
		if (am_read_room(line, &r, ser) == ERR)
			return (err(ser, &am, &r));
	if (!ft_strchr(line, '-') || am_addrooms(am, r, ser[0], ser[1]) == ERR)
		return (err(ser, &am, &r));
	ft_lstdel(&r, del);
	return (read_links(&am, line, fd));
}
