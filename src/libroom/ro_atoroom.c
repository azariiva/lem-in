/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ro_ro_atoroom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:03:18 by blinnea           #+#    #+#             */
/*   Updated: 2020/06/28 22:52:32 by blinnea          ###   ########.fr       */
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

t_room			*ro_atoroom(char *line)
{
	char		**data;
	t_room		*room;
	static int	rtype;

	if (line[0] == '#' || line[0] == 'L')
	{
		if (line[1] == '#')
		{
			line = ft_strtrim(line);
			if (!ft_strcmp(line + 2, "start"))
				rtype = START_ROOM;
			else if (!ft_strcmp(line + 2, "end"))
				rtype = END_ROOM;
			ft_strdel(&line);
		}
		return (NULL);
	}
	if (!line || !(data = ft_strsplit_plus(line, ft_isspace)))
		return (NULL);
	if (getdatasize(data) != 3 || !(isnum(data[1]) && isnum(data[2])))
	{
		free_data(&data);
		return (NULL);
	}
	room = ro_new(data[0], (t_coord){ft_atoi(data[1]), ft_atoi(data[2])}, rtype);
	free_data(&data);
	rtype = MIDDLE_ROOM;
	return (room);
}
