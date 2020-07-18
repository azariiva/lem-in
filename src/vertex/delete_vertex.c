/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_vertex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 19:50:55 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/18 19:53:57 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "vertex.h"

void	del(void *content, size_t content_size)
{
	if (content && content_size)
		ft_memdel(&content);
}

void	delete_vertex(t_vertex **vertex)
 {
	 if (!vertex || !*vertex)
	 	return ;
	if ((*vertex)->edges)
		ft_quedel(&((*vertex)->edges), del);
	ft_memdel((void **)vertex);
 }
