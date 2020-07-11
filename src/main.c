/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 04:00:37 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 04:26:07 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libway.h"
#include "algo.h"
#include <unistd.h>

int		main(void)
{
	t_am	*am;

	if (!(am = am_new(STDIN_FILENO)))
	{
		ft_putendl_fd("ERROR", STDERR_FILENO);
		return (-1);
	}
	if (find_shortest(am) != OK)
	{
		ft_putendl_fd("ERROR", STDERR_FILENO);
		am_del(&am);
		return (-1);
	}
	while (find_shortest(am) == OK)
		;
	ft_printf("\n");
	if (run_ants(am) == ERR)
	{
		am_del(&am);
		return (-1);
	}
	am_del(&am);
	return (0);
}
