/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_show.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 04:58:55 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/08 05:18:19 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libway.h"

void	way_show(t_way *way, t_room **rooms)
{
	size_t	i;

	i = -1;
	while (++i < way->len - 1)
		ft_printf("%s->", rooms[way->nodes[i]]->name);
	ft_printf("%s\n", rooms[way->nodes[way->len - 1]]->name);
}
