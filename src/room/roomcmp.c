/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roomcmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 19:27:14 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/18 19:28:54 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"

int	roomcmp(t_room *a, t_room *b)
{
	if (!strcmp(a->name, b->name))
		return (0);
	if (a->x == b->x)
		return (0);
	if (a->room_type != R_MID && a->room_type == b->room_type)
		return (0);
	return (1);
}
