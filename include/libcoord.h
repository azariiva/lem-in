/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcoord.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 22:43:39 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 03:51:52 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCOORD_H

# define LIBCOORD_H

typedef struct	s_coord
{
	int	x;
	int	y;
}				t_coord;

int				co_equal(t_coord a, t_coord b);

#endif
