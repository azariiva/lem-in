/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_removeflow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:38:23 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/08 02:20:25 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libam.h"

void	am_removeflow(t_am *am, size_t v)
{
	size_t	i;

	if (v == 0 || v == am->size - 1)
		return ;
	i = -1;
	while (++i < am->size)
	{
		if (am->flow[v][i])
		{
			am->flow[v][i] = 0;
			am->flow[i][v] = 0;
			am_removeflow(am, i);
		}
	}
}
