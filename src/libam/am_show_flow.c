/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_show_flow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:08:00 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 05:45:25 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libam.h"

static int	uintlen(size_t n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		++len;
		n /= 10;
	}
	return (len);
}

void		am_show_flow(t_am *am)
{
	int		max_len;
	size_t	i;
	size_t	j;

	max_len = uintlen(am->size);
	i = -1;
	ft_printf("%*c", max_len + 2, ' ');
	while (++i < am->size)
		ft_printf("{green}%*zu{eoc}| ", max_len, i);
	ft_printf("\n");
	i = -1;
	while (++i < am->size)
	{
		ft_printf("{green}%*zu{eoc}| ", max_len, i);
		j = -1;
		while (++j < am->size)
			ft_printf("%*d  ", max_len, am->f[i][j]);
		ft_printf("\n");
	}
}
