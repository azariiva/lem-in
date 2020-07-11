/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 17:47:25 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 06:16:17 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libam.h"

void	am_del(t_am **am)
{
	size_t	i;

	if (am && *am)
	{
		i = -1;
		while (++i < (*am)->size)
		{
			ro_del((*am)->r + i);
			ft_memdel((void **)((*am)->e + i));
			ft_memdel((void **)((*am)->f + i));
			ft_memdel((void **)((*am)->a + i));
		}
		ft_memdel((void **)&((*am)->r));
		ft_memdel((void **)&((*am)->e));
		ft_memdel((void **)&((*am)->f));
		ft_memdel((void **)&((*am)->a));
		ft_memdel((void **)am);
	}
}
