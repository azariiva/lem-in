/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhitmonc <lhitmonc@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 21:34:40 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/31 22:24:49 by lhitmonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static void		err(t_lem_in *lem_in)
{
	get_next_line(-1, NULL);
	delete_lem_in_content(lem_in);
	ft_printf_fd(STDERR_FILENO, "ERROR\n");
	exit(0);
}

void			helper_main(t_lem_in *lem_in, t_acav acav, int *fd)
{
	char		c;

	while ((c = ft_getopt(acav, ":i:l:o:")) != -1)
	{
		if (c == 'i' &&
		(fd[0] = open(g_optarg, O_RDONLY)) < 0)
			err(lem_in);
		else if (c == 'l' &&
		(fd[1] = open(g_optarg, O_WRONLY | O_CREAT | O_TRUNC, 0000666)) <= 0)
			err(lem_in);
		else if (c == 'o' &&
		(fd[2] = open(g_optarg, O_WRONLY | O_CREAT | O_TRUNC, 0000666)) <= 0)
			err(lem_in);
		else if (c == '?')
		{
			ft_printf("lem-in: unrecognized option \'-%c\'\n", g_optopt);
			ft_printf("Usage: [-i in] [-l log] [-o out]\n");
			exit(0);
		}
		else if (c == ':')
		{
			ft_printf("option \'-%c\' requires an argument\n", g_optopt);
			exit(0);
		}
	}
}

int				main(int ac, char **av)
{
	t_lem_in	lem_in;
	int			fd[3];

	fd[0] = STDIN_FILENO;
	fd[1] = -1;
	fd[2] = STDOUT_FILENO;
	ft_bzero(&lem_in, sizeof(t_lem_in));
	helper_main(&lem_in, (t_acav){.argc = ac, .argv = av}, fd);
	(fd[1] > 0 ? measure_time(fd[1], "#fill_lem_in") : 0);
	if (fill_lem_in(&lem_in, fd[0], fd[2]) == ERR)
		err(&lem_in);
	(fd[1] > 0 ? measure_time(fd[1], "#edmonds_karp") : 0);
	if (fd[0] != STDIN_FILENO)
		close(fd[0]);
	if (edmonds_karp(&lem_in) == ERR)
		err(&lem_in);
	(fd[1] > 0 ? measure_time(fd[1], "#send_ants") : 0);
	if (send_ants(&lem_in, fd[2]) == ERR)
		err(&lem_in);
	(fd[1] > 0 ? measure_time(fd[1], NULL) : 0);
	(fd[1] > 0 ? close(fd[1]) : 0);
	(fd[2] != STDOUT_FILENO ? close(fd[2]) : 0);
	delete_lem_in_content(&lem_in);
	return (0);
}
