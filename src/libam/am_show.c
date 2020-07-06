/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_show.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:45:00 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/06 16:25:53 by blinnea          ###   ########.fr       */
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

static void	print_rooms(t_am *am)
{
	size_t	i;
	int		len;
	int		max_len;

	max_len = uintlen(am->size - 1);
	i = -1;
	while (++i < am->size)
	{
		len = ft_strlen(am->rooms[i]->name);
		if (max_len < len)
			max_len = len;
	}
	max_len *= 2;
	i = -1;
	while (++i < am->size)
	{
		len = ft_strlen(am->rooms[i]->name) + 1;
		ft_printf("%*d|", max_len, i);
	}
	ft_printf("\n");
	i = -1;
	ft_printf("%*c", ft_strlen("Rooms: "), ' ');
	while (++i < am->size)
		ft_printf("%*s|", max_len, am->rooms[i]->name);
	ft_printf("\n");
}

static void	print_am(t_am *am)
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
			ft_printf("%*d  ", max_len, am->edges[i][j]);
		ft_printf("\n");
	}
}

void		am_show(t_am *am)
{
	ft_printf("Ants: %d\nSize: %zu\n", am->ants, am->size);
	ft_printf("Rooms: ");
	print_rooms(am);
	ft_printf("\n");
	print_am(am);
}
