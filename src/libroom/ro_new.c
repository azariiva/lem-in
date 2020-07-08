/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ro_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:03:20 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/08 18:19:50 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libroom.h"
#include <unistd.h>

t_room		*ro_new(char *name, t_coord coord, int rtype)
{
	t_room	*new;

	if ((new = ft_memalloc(sizeof(t_room))) == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "{red}Error:{eoc} allocation error.\n");
		return (NULL);
	}
	if ((new->name = ft_strdup(name)) == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "{red}Error:{eoc} allocation error.\n");
		ro_del(&new);
		return (NULL);
	}
	ft_memcpy(&(new->coord), &coord, sizeof(t_coord));
	new->weight = rtype;
	return (new);
}
