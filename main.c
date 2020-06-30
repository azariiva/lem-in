#include <stdio.h>
#include "libmap.h"
#include "fcntl.h"

// int				verify_rooms(t_list *rlist)
// {
// 	t_room	*room;
// 	t_list	*ptr;

// 	while (rlist->next)
// 	{
// 		room = *(t_room **)rlist->content;

// 	}
// 	room = *(t_room **)rlist->content;
// 	rlist = rlist->next;
// 	ptr = rlist->next;
// 	while (ptr)
// 	{
// 		if ()
// 	}
// }

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
