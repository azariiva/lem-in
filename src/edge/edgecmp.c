/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edgecmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 20:24:55 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/18 20:27:38 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edge.h"

int		edgecmp(t_edge *a, t_edge *b)
{
	if (!roomcmp(a->source->room, b->source->room) &&
	!roomcmp(a->sink->room, b->sink->room))
		return (0);
	return (1);
}
