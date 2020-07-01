/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 23:26:01 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/01 22:43:55 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "gnl_sup.h"
#include <sys/types.h>
#include <unistd.h>

static char	*list_to_str(t_list **list)
{
	size_t	len;
	t_list	*ptr;
	char	*str;

	ptr = *list;
	len = 0;
	while (ptr)
	{
		len += ptr->content_size;
		ptr = ptr->next;
	}
	if ((str = ft_strnew(len + 1)))
	{
		ptr = *list;
		while (ptr)
		{
			ft_strncat(str, ptr->content, ptr->content_size);
			ptr = ptr->next;
		}
	}
	ft_strlstdel(list);
	return (str);
}

static int	ft_read_strlst(t_list *fdlst, t_list **strlst, char **line, \
		char *buff)
{
	t_list	*ptr;
	char	*end_gnllloc;
	ssize_t	len;

	ptr = *strlst;
	while (1)
	{
		if ((end_gnllloc = ft_strchr(ptr->content, '\n')))
		{
			*end_gnllloc++ = 0;
			if (*end_gnllloc && !(fdlst->content = ft_lstnew(end_gnllloc, \
							sizeof(char) * (ptr->content_size - (end_gnllloc - \
									(char *)ptr->content)))))
				return (ERR);
			ptr->content_size = end_gnllloc - (char *)ptr->content;
			break ;
		}
		if (!(len = read(fdlst->content_size, buff, BUFF_SIZE)))
			break ;
		buff[len] = 0;
		if (!(ptr->next = ft_lstnew(buff, sizeof(char) * (len + 1))))
			return (ERR);
		ptr = ptr->next;
	}
	return ((*line = list_to_str(strlst)) ? OK : ERR);
}

static int	ft_read_fdlst(t_list *fdlst, char **line)
{
	t_list	*strlst;
	char	buff[BUFF_SIZE + 1];
	ssize_t	len;
	int		res;

	if (!(strlst = (t_list *)fdlst->content))
	{
		if ((len = read(fdlst->content_size, buff, BUFF_SIZE)) <= 0)
			return (len == 0 ? END : ERR);
		buff[len] = 0;
		if (!(strlst = ft_lstnew(buff, sizeof(char) * (len + 1))))
			return (ERR);
	}
	fdlst->content = NULL;
	if ((res = ft_read_strlst(fdlst, &strlst, line, buff)) == ERR)
		ft_strlstdel(&strlst);
	return (res);
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*fdlst;
	t_list			*ptr;
	int				res;

	if (fd == -1)
		return (ft_fdlstdel(&fdlst) | END);
	ptr = fdlst;
	while (ptr)
	{
		if (ptr->content_size == (size_t)fd)
		{
			if ((res = ft_read_fdlst(ptr, line)) == ERR)
				ptr->content = NULL;
			return (res);
		}
		ptr = ptr->next;
	}
	if (!(ptr = ft_lstnew_ic(fd)))
		return (ERR);
	ft_lstadd(&fdlst, ptr);
	if ((res = ft_read_fdlst(fdlst, line)) == ERR)
		fdlst->content = NULL;
	return (res);
}
