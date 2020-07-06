#include "algo.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int		main(void)
{
	t_am	*am;
	int		fd;

	fd = open("/Users/blinnea/Documents/lem-in/test.txt", O_RDONLY);
	if (!(am = am_new(fd)))
		return (-1);
	close(fd);
	find_shortest(am);
	// while (find_shortest(am) == OK)
	// 	;
	am_show(am);
	am_del(&am);
	return (0);
}
