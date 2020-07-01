/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_sup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 12:37:24 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/01 22:45:07 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

void	ft_strlstdel(t_list **alst)
{
	t_list	*ptr;
	t_list	*todel;

	ptr = *alst;
	while (ptr)
	{
		todel = ptr;
		ptr = ptr->next;
		ft_memdel(&(todel->content));
		ft_memdel((void **)&todel);
	}
	*alst = NULL;
}

int		ft_fdlstdel(t_list **fdlst)
{
	t_list	*ptr;
	t_list	*todel;

	ptr = *fdlst;
	while (ptr)
	{
		todel = ptr;
		ptr = ptr->next;
		ft_strlstdel((t_list **)&(todel->content));
		ft_memdel((void **)&todel);
	}
	*fdlst = NULL;
	return (0);
}
