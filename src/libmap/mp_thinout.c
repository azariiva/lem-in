/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_thinout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:49:40 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/02 00:41:14 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmap.h"

static void	del(void *content, size_t size)
{
	if (!size)
		ft_memdel(&content);
}

// static void	helper1(t_list **links)
// {
// 	t_list	*ptr;
// 	t_list	*todel;

// 	while ((*links) && (*links)->content_size == 0)
// 	{
// 		todel = *links;
// 		*links = todel->next;
// 		ft_lstdelone(&todel, del);
// 	}
// 	if (!*links)
// 		return ;
// 	ptr = *links;
// 	while (ptr->next)
// 	{
// 		if (ptr->next->content_size == 0)
// 		{
// 			todel = ptr->next;
// 			ptr->next = ptr->next->next;
// 			ft_lstdelone(&todel, del);
// 		}
// 		else
// 			ptr = ptr->next;
// 	}
// }

// static void	del(void *content, size_t size)
// {
// 	if (size && content)
// 		ro_free((t_room **)content);
// }

static void	helper(t_list **middle)
{
	t_list	*ptr;
	t_list	*todel;
	int		flag;

	flag = 1;
	while (flag)
	{
		flag = 0;
		while (!(*((t_room **)(*middle)->content))->links)
		{
			todel = *middle;
			*middle = (*middle)->next;
			ft_lstdelone(&todel, del);

		}
		ptr = *middle;
		while (ptr->next)
		{
			if (!(*((t_room **)ptr->next->content))->links)
			{
				todel = ptr->next;
				ptr->next = ptr->next->next;
				ft_lstdelone(&todel, del);
			}
		}
	}
}


void		mp_thinout(t_map *map)
{
	t_queue	*queue;
	t_list	*u;
	t_list	*v;

	queue = ft_quenew(&(map->start), sizeof(t_room *));
	while (!ft_queisempty(queue))
	{
		u = ft_quepop(queue);
		v = (*(t_room **)u->content)->links;
		while (v)
		{
			if ((*(t_room **)v->content)->weight <= (*(t_room **)u->content)->weight)
				v->content_size = 0;
			v = v->next;
		}
		ft_lstdelone(&u, del);
	}
	ft_quedel(&queue, del);
	helper(&(map->middle));
}