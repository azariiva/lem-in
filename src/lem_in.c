/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 21:34:40 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/31 12:44:52 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "mtime.h"
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

const char		*opstring = ":i:l:o:";

int				main(int ac, char **av)
{
	t_lem_in	lem_in;
	int			fdlog;
	int			fdin;
	int			fdout;
	char		c;

	fdin = STDIN_FILENO;
	fdlog = STDOUT_FILENO;
	fdout = STDOUT_FILENO;
	ft_bzero(&lem_in, sizeof(t_lem_in));
	while ((c = ft_getopt((t_acav){.argc = ac, .argv = av}, opstring)) != -1)
	{
		if (c == 'i' &&
		(fdin = open(g_optarg, O_RDONLY)) < 0)
			err(&lem_in);
		else if (c == 'l' &&
		(fdlog = open(g_optarg, O_WRONLY | O_CREAT | O_TRUNC, 0000666)) <= 0)
			err(&lem_in);
		else if (c == 'o' &&
		(fdout = open(g_optarg, O_WRONLY | O_CREAT | O_TRUNC, 0000666)) <= 0)
			err(&lem_in);
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
	measure_time(fdlog, "#fill_lem_in");
	if (fill_lem_in(&lem_in, fdin, fdout) == ERR)
		err(&lem_in);
	measure_time(fdlog, "#edmonds_karp");
	if (fdin != STDIN_FILENO)
		close(fdin);
	if (edmonds_karp(&lem_in) == ERR)
		err(&lem_in);
	measure_time(fdlog, "#send_ants");
	ft_printf_fd(fdout, "\n");
	if (send_ants(&lem_in, fdout) == ERR)
		err(&lem_in);
	measure_time(fdlog, NULL);
	if (fdlog != STDOUT_FILENO)
		close(fdlog);
	if (fdout != STDOUT_FILENO)
		close(fdout);
	delete_lem_in_content(&lem_in);
	return (0);
}
