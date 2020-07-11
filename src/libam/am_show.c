/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_show.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:45:00 by blinnea           #+#    #+#             */
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

static void	print_rooms(t_am *am)
{
	size_t	i;
	int		len;
	int		max_len;

	max_len = uintlen(am->size - 1);
	i = -1;
	while (++i < am->size)
	{
		len = ft_strlen(am->r[i]->name);
		if (max_len < len)
			max_len = len;
	}
	max_len *= 2;
	i = -1;
	while (++i < am->size)
	{
		len = ft_strlen(am->r[i]->name) + 1;
		ft_printf("%*d|", max_len, i);
	}
	ft_printf("\n");
	i = -1;
	ft_printf("%*c", ft_strlen("r: "), ' ');
	while (++i < am->size)
		ft_printf("%*s|", max_len, am->r[i]->name);
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
			ft_printf("%*d  ", max_len, am->e[i][j]);
		ft_printf("\n");
	}
}

static void	print_found_paths(t_am *am)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < am->size)
	{
		j = -1;
		while (++j < am->size)
		{
			if (am->f[i][j] == 1)
				ft_printf("%s->%s\n", am->r[i]->name, am->r[j]->name);
		}
	}
}

void		am_show(t_am *am)
{
	ft_printf("Ants: %d\nSize: %zu\n", am->ants, am->size);
	ft_printf("r: ");
	print_rooms(am);
	ft_printf("\n");
	print_am(am);
	ft_printf("\n");
	print_found_paths(am);
}
