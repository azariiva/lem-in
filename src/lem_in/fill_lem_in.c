/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lem_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 20:45:56 by blinnea           #+#    #+#             */
/*   Updated: 2020/08/01 11:14:17 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	**init_arr(size_t size)
{
	char			**arr;
	char			*ptr;
	size_t register	i;
	size_t			len;

	len = sizeof(char *) * size * 2 + sizeof(char) * size * size * 4;
	if (!(arr = ft_memalloc(len)))
		return (NULL);
	ptr = (char *)(arr + size * 2);
	i = -1;
	while (++i < size * 2)
		arr[i] = (ptr + i * size * 2);
	return (arr);
}

static bool	isnum(char *line)
{
	while (*line)
	{
		if (!ft_isdigit(*line))
			return (false);
		++line;
	}
	return (true);
}

int			fill_lem_in(t_lem_in *lem_in, int fdin, int fdout)
{
	char	*line;

	line = NULL;
	if (get_next_line(fdin, &line) != OK || !isnum(line) ||
	(lem_in->ants_size = ft_atoi(line)) <= 0)
	{
		ft_strdel(&line);
		return (ERR);
	}
	ft_printf_fd(fdout, "%s\n", line);
	ft_strdel(&line);
	if (!(lem_in->ants = ft_memalloc(lem_in->ants_size * sizeof(t_list *))) ||
	!(lem_in->rooms = create_rooms(fdin, fdout, &line, &(lem_in->size))) ||
	!(lem_in->rooms[0].name) || !(lem_in->rooms[1].name) ||
	!(lem_in->visited = ft_memalloc(lem_in->size * 2 * sizeof(bool))))
		return (ERR);
	sort_rooms(lem_in->rooms, 2, lem_in->size - 1);
	if (!line || !(lem_in->flow = init_arr(lem_in->size)) ||
	!(lem_in->path = init_arr(lem_in->size)) ||
	!(lem_in->residual_network = init_arr(lem_in->size)) ||
	!(lem_in->capacity = init_arr(lem_in->size)) ||
	fill_graph(lem_in, &line, fdin, fdout) == ERR)
		return (ERR);
	return (OK);
}
