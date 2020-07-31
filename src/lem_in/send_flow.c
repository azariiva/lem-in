/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_flow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:38:18 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/31 15:40:52 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	send_flow(t_lem_in *lem_in, char pv)
{
	size_t register	i;
	size_t register	j;

	i = 2;
	while (i != 1)
	{
		j = 0;
		while (++j < lem_in->size * 2)
			if (lem_in->path[j][i] == pv)
			{
				lem_in->flow[j][i] += 1;
				lem_in->flow[i][j] -= 1;
				lem_in->residual_network[i][j] =
				lem_in->capacity[i][j] - lem_in->flow[i][j];
				lem_in->residual_network[j][i] =
				lem_in->capacity[j][i] - lem_in->flow[j][i];
				i = j;
				break ;
			}
	}
}
