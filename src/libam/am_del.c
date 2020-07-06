/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 17:47:25 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/06 15:14:30 by blinnea          ###   ########.fr       */
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
		ft_memdel((void **)((*am)->edges + i));
		ft_memdel((void **)((*am)->resedges + i));
	}
	ft_memdel((void **)&((*am)->rooms));
	ft_memdel((void **)&((*am)->edges));
	ft_memdel((void **)&((*am)->resedges));
	ft_memdel((void **)am);
}
