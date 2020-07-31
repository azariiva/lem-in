/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slink.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhitmonc <lhitmonc@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 21:30:25 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/31 23:09:34 by lhitmonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static size_t		getlinksize(char **link)
{
	size_t	ctr;

	ctr = 0;
	while (link[ctr] != NULL && link[ctr][0])
		++ctr;
	return (ctr);
}

void				free_slink(char ***link)
{
	char	**ptr;

	ptr = *link;
	while (*ptr)
		ft_memdel((void **)ptr++);
	ft_memdel((void **)link);
}

char				**atoslink(char *line)
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
		free_slink(&link);
		return (NULL);
	}
	return (link);
}
