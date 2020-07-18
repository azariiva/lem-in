/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoroom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 19:20:29 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/18 19:25:51 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"

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

t_room		*atoroom(char *line, t_room_type room_type)
{
	char	**data;
	t_room	*room;

	if (!line || !(data = ft_strsplit_plus(line, ft_isspace)))
		return (NULL);
	if (getdatasize(data) != 3 || !(isnum(data[1]) && isnum(data[2])))
	{
		free_data(&data);
		return (NULL);
	}
	room = new_room(data[0], ft_atoi(data[1]), ft_atoi(data[2]), room_type);
	free_data(&data);
	return (room);
}
