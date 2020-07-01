/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ro_ro_atoslink.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 20:05:00 by blinnea           #+#    #+#             */
/*   Updated: 2020/06/28 22:53:23 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmap.h"
#include <unistd.h>

static void			free_link(char **link)
{
	char	**ptr;

	ptr = link;
	while (*ptr)
		ft_memdel((void **)ptr++);
	ft_memdel((void **)&link);
}

static size_t		getlinksize(char **link)
{
	size_t	ctr;

	ctr = 0;
	while (link[ctr] != NULL)
		++ctr;
	return (ctr);
}

static char			**mp_atoslink(char *line)
{
	char	**link;
	char	*trimmed;

	if ((trimmed = ft_strtrim(line)) == NULL)
	{
		ft_putendl_fd("Error: mp_atoslink ft_strtrim returns null pointer",\
		STDERR_FILENO);
		return (NULL);
	}
	if ((link = ft_strsplit(trimmed, '-')) == NULL)
	{
		ft_putendl_fd("Error: mp_atoslink ft_strsplit returns null pointer",\
		STDERR_FILENO);
		ft_memdel((void **)&trimmed);
		return (NULL);
	}
	ft_memdel((void **)&trimmed);
	if (getlinksize(link) != 2)
	{
		ft_putendl_fd("Error: mp_atoslink multiple links in one line",\
		STDERR_FILENO);
		free_link(link);
		return (NULL);
	}
	return (link);
}

int					mp_atolink(t_map *map, char *line)
{
	char	**slink;
	t_room	*link[2];

	if (!(slink = mp_atoslink(line)))
		return (ERR);
	if (!ft_strcmp(slink[0], slink[1]))
	{
		ft_putendl_fd("Error: mp_atolink room connects to itself",\
		STDERR_FILENO);
		return (ERR);
	}
	if (!(link[0] = mp_find(map, slink[0])) ||\
	!(link[1] = mp_find(map, slink[1])))
	{
		ft_putendl_fd("Error: mp_atolink room not found", STDERR_FILENO);
		free_link(slink);
		return (ERR);
	}
	free_link(slink);
	if (link[0] == map->start || link[1] == map->end)
		return (ro_connect(link[0], link[1], SINGLE_LINK));
	if (link[1] == map->start || link[0] == map->end)
		return (ro_connect(link[1], link[0], SINGLE_LINK));
	else
		return (ro_connect(link[0], link[1], DOUBLE_LINK));
}
