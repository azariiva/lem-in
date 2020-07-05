#include "libmap.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int		main(void)
{
	t_map	*map;

	if (!(map = mp_new(STDIN_FILENO)))
		return (-1);
	mp_giveweight(map);
	mp_thinout(map);
	mp_show(map);
	mp_free(&map);
	return (0);
}
