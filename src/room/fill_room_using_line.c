/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_room_using_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhitmonc <lhitmonc@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 15:04:40 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/31 23:00:25 by lhitmonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"

static void		free_data(char ***data)
{
	char	**ptr;

	ptr = *data;
	while (*ptr)
		ft_strdel(ptr++);
	ft_memdel((void **)data);
}

static int		isnum(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}

static char		**getdata(char *line)
{
	size_t			ctr;
	char			**data;

	if (!(data = ft_strsplit_plus(line, ft_isspace)))
		return (NULL);
	ctr = 0;
	while (data[ctr] != NULL)
		++ctr;
	if (ctr != 3 || !(isnum(data[1]) && isnum(data[2])))
	{
		free_data(&data);
		return (NULL);
	}
	return (data);
}

static int		exit__(char **trimmed, int rc)
{
	ft_strdel(trimmed);
	return (rc);
}

int				fill_room_using_line(t_room *room, char *line)
{
	char	**data;
	char	*trimmed;

	if (!(trimmed = ft_strtrim(line)))
		return (ERR);
	if (trimmed[0] == 'L')
		return (exit__(&trimmed, ERR));
	if (trimmed[0] == '#')
	{
		if (!ft_strcmp(trimmed + 1, "#start"))
			room->weight = 1;
		if (!ft_strcmp(trimmed + 1, "#end"))
			room->weight = 2;
		return (exit__(&trimmed, END));
	}
	else if (!(data = getdata(trimmed)))
		return (exit__(&trimmed, ERR));
	fill_room(room, data[0], ft_atoi(data[1]), ft_atoi(data[2]));
	free_data(&data);
	return (exit__(&trimmed, OK));
}
