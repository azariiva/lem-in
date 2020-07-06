/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_removeflow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:38:23 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/06 21:40:36 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libam.h"

void	am_removeflow(t_am *am, size_t v)
{
	size_t	i;

	i = -1;
	while (++i < am->size)
	{
		if (am->flow[v][i])
		{
			am->flow[v][i] = 0;
			am_removeflow(am, i);
		}
	}
}
