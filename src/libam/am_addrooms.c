/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_addrooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 06:32:06 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 06:32:17 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libam.h"

int	am_addrooms(t_am *am, t_list *r, t_room *start, t_room *end)
{
	size_t	i;

	if (!start || !end)
		return (ERR);
	am->size = ft_lstsize(r) + 2;
	am->r = ft_memalloc(am->size * sizeof(t_room *));
	am->e = ft_memalloc(am->size * sizeof(int *));
	am->f = ft_memalloc(am->size * sizeof(int *));
	am->a = ft_memalloc(am->size * sizeof(int *));
	i = -1;
	while (++i < am->size)
	{
		am->e[i] = ft_memalloc(am->size * sizeof(int));
		am->f[i] = ft_memalloc(am->size * sizeof(int));
		am->a[i] = ft_memalloc(am->size * sizeof(int));
	}
	am->r[0] = start;
	am->r[am->size - 1] = end;
	i = 0;
	while (++i < am->size - 1)
	{
		am->r[i] = *(t_room **)r->content;
		r = r->next;
	}
	return (OK);
}
