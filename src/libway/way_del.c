/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:53:04 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/08 17:58:45 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libway.h"

void	way_del(t_way **way)
{
	t_way	*ptr;

	ptr = *way;
	while (ptr->len)
	{
		ft_memdel((void **)&(ptr->nodes));
		++ptr;
	}
	ft_memdel((void **)way);
}
