/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 17:47:25 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/05 17:57:33 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libam.h"

void	am_del(t_am **am)
{
	size_t	i;

	i = -1;
	while (++i < (*am)->size)
	{
		ro_del((*am)->rooms + i);
		ft_memdel((*am)->edges + i);
		ft_memdel((*am)->resedges + i);
	}
	ft_memdel(&((*am)->rooms));
	ft_memdel(&((*am)->edges));
	ft_memdel(&((*am)->resedges));
	ft_memdel(am);
}
