/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_clear_addgraph.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 19:24:59 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/06 20:37:56 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libam.h"

void	am_clear_addgraph(t_am *am)
{
	size_t	idx;

	idx = -1;
	while (++idx < am->size)
		ft_bzero((void *)am->addgraph[idx], am->size * sizeof(int));
}
