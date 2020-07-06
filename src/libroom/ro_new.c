/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ro_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:03:20 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/06 21:14:23 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libroom.h"
#include <unistd.h>

t_room		*ro_new(char *name, t_coord coord, int rtype)
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
		ro_del(&new);
		return (NULL);
	}
	ft_memcpy(&(new->coord), &coord, sizeof(t_coord));
	new->weight = rtype;
	return (new);
}
