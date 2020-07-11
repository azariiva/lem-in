/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ro_atoroom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:03:18 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 05:37:33 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libroom.h"
#include <unistd.h>

static void		free_data(char ***data)
{
	char	**ptr;

	ptr = *data;
	while (*ptr)
		ft_memdel((void **)ptr++);
	ft_memdel((void **)data);
}

static int		isnum(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		++str;
	}
	return (1);
}

static size_t	getdatasize(char **data)
{
	size_t	ctr;

	ctr = 0;
	while (data[ctr] != NULL)
		++ctr;
	return (ctr);
}

static char		**get_data(char *line)
{
	char		**data;

	if (!(data = ft_strsplit_plus(line, ft_isspace)))
		return (NULL);
	if (getdatasize(data) != 3 || !(isnum(data[1]) && isnum(data[2])))
	{
		free_data(&data);
		return (NULL);
	}
	return (data);
}

t_room			*ro_atoroom(char *line)
{
	char		**data;
	t_room		*room;
	static int	rt;

	if (line[0] == 'L')
		return ((t_room *)ERR);
	else if (line[0] == '#')
	{
		if (line[1] == '#')
		{
			line = ft_strtrim(line);
			if (!ft_strcmp(line + 2, "start"))
				rt = SR;
			else if (!ft_strcmp(line + 2, "end"))
				rt = ER;
			ft_strdel(&line);
		}
		return ((t_room *)OK);
	}
	if (!(data = get_data(line)))
		return ((t_room *)ERR);
	room = ro_new(data[0], (t_coord){ft_atoi(data[1]), ft_atoi(data[2])}, rt);
	free_data(&data);
	rt = MIDDLE_ROOM;
	return (room ? room : (t_room *)ERR);
}
