/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_lem_in_content.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 21:37:12 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/23 19:30:04 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	delete_lem_in_content(t_lem_in *lem_in)
{
	if (lem_in->rooms)
		delete_rooms(&(lem_in->rooms), lem_in->size);
	if (lem_in->flow)
		ft_memdel((void **)&(lem_in->flow));
	if (lem_in->path)
		ft_memdel((void **)&(lem_in->path));
	if (lem_in->old_flow)
		ft_memdel((void **)&(lem_in->old_flow));
	if (lem_in->residual_network)
		ft_memdel((void **)&(lem_in->residual_network));
	if (lem_in->capacity)
		ft_memdel((void **)&(lem_in->capacity));
	if (lem_in->visited)
		ft_memdel((void **)&(lem_in->visited));
	if (lem_in->ants)
		ft_memdel((void **)&(lem_in->ants));
}
