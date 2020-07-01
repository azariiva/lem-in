#include "libmap.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int		main(void)
{
	t_map	*map;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	if (!(map = mp_new(fd)))
		return (-1);
	close(fd);
	mp_giveweight(map);
	mp_thinout(map);
	mp_show(map);
	mp_free(&map);
	return (0);
}
