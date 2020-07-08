/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 17:47:25 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/07 14:36:44 by blinnea          ###   ########.fr       */
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
		ft_memdel((void **)((*am)->flow + i));
		ft_memdel((void **)((*am)->addgraph + i));
	}
	ft_memdel((void **)&((*am)->rooms));
	ft_memdel((void **)&((*am)->edges));
	ft_memdel((void **)&((*am)->flow));
	ft_memdel((void **)&((*am)->addgraph));
	ft_memdel((void **)am);
}
