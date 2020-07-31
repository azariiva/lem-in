/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 17:30:38 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/31 11:34:02 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"

static void	swap(t_room *a, t_room *b)
{
	t_room	tmp;

	roomcpy(&tmp, a);
	roomcpy(a, b);
	roomcpy(b, &tmp);
}

void		sort_rooms(t_room *rooms, long long low, long long high)
{
	long long	i;
	long long	j;
	long long	p;

	i = low;
	j = high;
	p = low;
	if (i >= j)
		return ;
	while (i < j)
	{
		while (ft_strcmp(rooms[i].name, rooms[p].name) < 0 && i < high)
			++i;
		while (ft_strcmp(rooms[j].name, rooms[p].name) > 0)
			j--;
		if (i < j)
			swap(rooms + i, rooms + j);
	}
	swap(rooms + p, rooms + j);
	sort_rooms(rooms, low, j - 1);
	sort_rooms(rooms, j + 1, high);
}
