#include "libway.h"
#include "algo.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int		main(void)
{
	t_am	*am;
	int		fd;
	// t_way	*ways;
	// t_way	*ptr;

	fd = open("test.txt", O_RDONLY);
	if (!(am = am_new(fd)))
		return (-1);
	close(fd);
	if (find_shortest(am) != OK)
		ft_printf_fd(STDERR_FILENO, "{red}Error:{eoc} path doesn't exist.");
	while (find_shortest(am) == OK)
		;
	run_ants(am);
	// am_show(am);
	// ways = way_find_all(am);
	// ptr = ways;
	// while (ptr->len)
	// {
	// 	way_show(ptr, am->rooms);
	// 	++ptr;
	// }
	am_del(&am);
	return (0);
}
