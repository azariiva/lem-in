/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 21:31:49 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/31 21:54:31 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <unistd.h>

static void			helper(t_lem_in *lem_in)
{
	size_t register	i;

	i = -1;
	while (++i < lem_in->size)
	{
		lem_in->residual_network[i * 2][i * 2 + 1] = 1;
		lem_in->residual_network[i * 2 + 1][i * 2] = 0;
		lem_in->capacity[i * 2 + 1][i * 2] = -1;
		lem_in->capacity[i * 2][i * 2 + 1] = 1;
	}
}

static int			exit__(char ***slink, char **line, int rcode)
{
	if (*line)
		ft_strdel(line);
	if (*slink)
		free_slink(slink);
	return (rcode);
}

static void			big_assign(t_lem_in *lem_in, size_t const link[2])
{
	lem_in->capacity[link[0] * 2 + 1][link[1] * 2] = 1;
	lem_in->capacity[link[1] * 2 + 1][link[0] * 2] = 1;
	lem_in->residual_network[link[0] * 2 + 1][link[1] * 2] = 1;
	lem_in->residual_network[link[1] * 2 + 1][link[0] * 2] = 1;
}

int					fill_graph(t_lem_in *lem_in, char **line, int fdin,
int fdout)
{
	char	**slink;
	size_t	link[2];

	slink = NULL;
	helper(lem_in);
	while (1)
	{
		ft_printf_fd(fdout, "%s\n", *line);
		if ((*line)[0] == 'L')
			return (exit__(&slink, line, ERR));
		if ((*line)[0] != '#')
		{
			if (!(slink = atoslink(*line)) ||
			(link[0] = get_room_index(lem_in->rooms, lem_in->size, slink[0])) ==
			(size_t)-1 || (link[1] = get_room_index(lem_in->rooms, lem_in->size,
			slink[1])) == (size_t)-1 ||
			lem_in->capacity[link[0] * 2 + 1][link[1] * 2])
				return (exit__(&slink, line, ERR));
			ft_strdel(line);
			free_slink(&slink);
			big_assign(lem_in, link);
		}
		if (get_next_line(fdin, line) != OK)
			return (exit__(&slink, line, OK));
	}
}
