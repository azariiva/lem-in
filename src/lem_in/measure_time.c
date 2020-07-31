/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   measure_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blinnea <blinnea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:58:38 by blinnea           #+#    #+#             */
/*   Updated: 2020/07/30 18:25:24 by blinnea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/time.h>

void	measure_time(int fd, const char* name)
{
	static struct timeval	start;
	static struct timeval	stop;
	static const char		*nname;

	if (!nname)
	{
		gettimeofday(&start, NULL);
		nname = name;
	}
	else
	{
		gettimeofday(&stop, NULL);
		ft_printf_fd(fd, "%s took: %llu ms\n", nname,
		(stop.tv_sec - start.tv_sec) * 1000 +
		(stop.tv_usec - start.tv_usec) / 1000);
		nname = name;
		gettimeofday(&start, NULL);
	}
}
