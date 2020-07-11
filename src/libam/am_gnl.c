/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 03:08:48 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 03:25:17 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libam.h"

static void	del(void *c, size_t s)
{
	if (s && c)
	{
		ft_strdel((char **)c);
		ft_memdel(&c);
	}
}

static int	echo(char **line, int cmd)
{
	static t_queue	*q;
	t_list			*l;

	if (!q && !(q = ft_memalloc(sizeof(t_queue))))
		return (ERR);
	if (cmd == EC_ADD)
	{
		if (!(l = ft_lstnew(line, sizeof(char **))))
		{
			ft_quedel(&q, del);
			return (ERR);
		}
		ft_queadd(q, l);
		return (OK);
	}
	else if (cmd == EC_SHOW)
	{
		while (!ft_queisempty(q))
		{
			l = ft_quepop(q);
			ft_printf("%s\n", *(char **)l->content);
			ft_lstdelone(&l, del);
		}
	}
	ft_quedel(&q, del);
	return (END);
}

int			am_gnl(int fd, char **line)
{
	int		rc;

	if (fd == -1)
		return (echo(line, EC_DEL));
	if ((rc = get_next_line(fd, line)) == END)
	{
		echo(NULL, EC_SHOW);
		return (END);
	}
	else if (rc == ERR)
	{
		echo(NULL, EC_DEL);
		return (ERR);
	}
	if (echo(line, EC_ADD) == ERR)
		return (ERR);
	return (OK);
}
