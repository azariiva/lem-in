/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ro_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:03:20 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/01 22:35:20 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libroom.h"
#include <unistd.h>

t_room		*ro_new(char *name, t_coord coord)
{
	t_room	*new;

	if ((new = ft_memalloc(sizeof(t_room))) == NULL)
	{
		ft_putendl_fd("Error: ro_new allocation error", STDERR_FILENO);
		return (NULL);
	}
	if ((new->name = ft_strdup(name)) == NULL)
	{
		ft_putendl_fd("Error: ro_new allocation error", STDERR_FILENO);
		ro_free(&new);
		return (NULL);
	}
	ft_memcpy(&(new->coord), &coord, sizeof(t_coord));
	new->weight = INT_MAX;
	return (new);
}
