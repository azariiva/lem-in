/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 04:00:37 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/11 06:26:15 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libway.h"
#include "algo.h"
#include <unistd.h>

static int	throw_error(t_am **am)
{
	ft_putendl_fd("ERROR", STDERR_FILENO);
	am_del(am);
	return (-1);
}

int			main(void)
{
	t_am	*am;
	int		rc;

	if (!(am = am_new(STDIN_FILENO)))
		return (throw_error(NULL));
	if (find_shortest(am) != OK)
		return (throw_error(&am));
	while ((rc = find_shortest(am)) == OK)
		;
	if (rc == ERR)
		return (throw_error(&am));
	if (ft_printf("\n") && run_ants(am) == ERR)
		return (throw_error(&am));
	am_del(&am);
	return (0);
}
