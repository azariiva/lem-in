/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_str_to_idx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:19:27 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 05:40:48 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libam.h"

size_t	am_str_to_idx(char *str, t_am *am)
{
	size_t	idx;

	idx = -1;
	while (++idx < am->size)
	{
		if (!ft_strcmp(str, am->r[idx]->name))
			return (idx);
	}
	return (-1);
}
