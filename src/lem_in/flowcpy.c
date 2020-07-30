/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flowcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:36:14 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/30 18:47:25 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <string.h>

void	flowcpy(char **dst, char **src, size_t size)
{
	size_t	ignore;

	ignore = size * 2;
	ft_memcpy(dst + ignore, src + ignore, size * size * 4);
}
