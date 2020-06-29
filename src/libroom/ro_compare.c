/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ro_compare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 22:56:19 by blinnea           #+#    #+#             */
/*   Updated: 2020/06/29 14:52:21 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libroom.h"

int			ro_compare(t_room *a, t_room *b)
{
	return (co_equal(a->coord, b->coord) || !ft_strcmp(a->name, b->name));
}
