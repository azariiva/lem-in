/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_addlink.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:24:46 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 03:40:58 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libam.h"
#include <unistd.h>

static size_t		getlinksize(char **link)
{
	size_t	ctr;

	ctr = 0;
	while (link[ctr] != NULL)
		++ctr;
	return (ctr);
}

static void			free_slink(char **link)
{
	char	**ptr;

	ptr = link;
	while (*ptr)
		ft_memdel((void **)ptr++);
	ft_memdel((void **)&link);
}

static char			**am_atoslink(char *line)
{
	char	**link;
	char	*trimmed;

	if ((trimmed = ft_strtrim(line)) == NULL)
		return (NULL);
	if ((link = ft_strsplit(trimmed, '-')) == NULL)
	{
		ft_strdel(&trimmed);
		return (NULL);
	}
	ft_strdel(&trimmed);
	if (getlinksize(link) != 2)
	{
		free_slink(link);
		return (NULL);
	}
	if (!ft_strcmp(link[0], link[1]))
	{
		free_slink(link);
		return (NULL);
	}
	return (link);
}

int					am_addlink(char *line, t_am *am)
{
	char	**slink;
	int		link[2];

	if (line[0] == '#')
		return (OK);
	if (!(slink = am_atoslink(line)))
		return (ERR);
	if ((int)(link[0] = am_str_to_idx(slink[0], am)) == -1 ||
	(int)(link[1] = am_str_to_idx(slink[1], am)) == -1)
	{
		free_slink(slink);
		return (ERR);
	}
	free_slink(slink);
	if (am->edges[link[0]][link[1]] || am->edges[link[1]][link[0]])
		return (ERR);
	am->edges[link[0]][link[1]] = 1;
	am->edges[link[1]][link[0]] = 1;
	return (OK);
}
