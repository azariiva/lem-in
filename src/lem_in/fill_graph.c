/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 21:31:49 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/31 16:24:38 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
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

static char			**atoslink(char *line)
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
	if (getlinksize(link) != 2 || !ft_strcmp(link[0], link[1]))
	{
		free_slink(link);
		return (NULL);
	}
	return (link);
}

static void			helper(t_lem_in *lem_in)
{
	size_t 	i;

	i = -1;
	while (++i < lem_in->size)
	{
		lem_in->residual_network[i * 2][i * 2 + 1] = 1;
		lem_in->residual_network[i * 2 + 1][i * 2] = 0;
		lem_in->capacity[i * 2 + 1][i * 2] = -1;
		lem_in->capacity[i * 2][i * 2 + 1] = 1;
	}
}

int					fill_graph(t_lem_in *lem_in, char **line, int fdin,
int fdout)
{
	char	**slink;
	size_t	link[2];

	helper(lem_in);
	do
	{
		ft_printf_fd(fdout, "%s\n", *line);
		if ((*line)[0] == 'L')
		{
			ft_strdel(line);
			return (ERR);
		}
		if ((*line)[0] != '#')
		{
			if (!(slink = atoslink(*line)))
			{
				ft_strdel(line);
				return (ERR);
			}
			ft_strdel(line);
			if ((link[0] = get_room_index(lem_in->rooms, lem_in->size,
			slink[0])) == (size_t)-1 || (link[1] = get_room_index(lem_in->rooms,
			lem_in->size, slink[1])) == (size_t)-1)
			{
				free_slink(slink);
				return (ERR);
			}
			free_slink(slink);
			if (lem_in->capacity[link[0] * 2 + 1][link[1] * 2])
				return (ERR);
			lem_in->capacity[link[0] * 2 + 1][link[1] * 2] = 1;
			lem_in->capacity[link[1] * 2 + 1][link[0] * 2] = 1;
			lem_in->residual_network[link[0] * 2 + 1][link[1] * 2] = 1;
			lem_in->residual_network[link[1] * 2 + 1][link[0] * 2] = 1;
		}
	} while (get_next_line(fdin, line) == OK);
	if (line)
		ft_strdel(line);
	return (OK);
}
