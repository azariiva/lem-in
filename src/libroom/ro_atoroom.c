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
	char	**data;
	t_room	*room;

	if (!line || !(data = ft_strsplit_plus(line, ft_isspace)))
		return (NULL);
	if (getdatasize(data) != 3 || !(isnum(data[1]) && isnum(data[2])))
	{
		ft_putendl_fd("Error: ro_atoroom wrong line", STDERR_FILENO);
		free_data(&data);
		return (NULL);
	}
	room = ro_new(data[0], (t_coord){ft_atoi(data[1]), ft_atoi(data[2])});
	free_data(&data);
	return (room);
}
