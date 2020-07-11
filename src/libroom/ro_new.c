/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ro_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:03:20 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 05:43:52 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libroom.h"
#include <unistd.h>

t_room		*ro_new(char *name, t_coord c, int rtype)
{
	t_room	*new;

	if ((new = ft_memalloc(sizeof(t_room))) == NULL)
		return (NULL);
	if ((new->name = ft_strdup(name)) == NULL)
	{
		ro_del(&new);
		return (NULL);
	}
	ft_memcpy(&(new->c), &c, sizeof(t_coord));
	new->w = rtype;
	return (new);
}
