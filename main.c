#include <stdio.h>
#include "libmap.h"

void	show(t_room *room)
{
	if (!room)
		printf("(null)\n");
	else
		printf("name: %s\t\tcoord: %d %d\n", room->name,\
		room->coord.x, room->coord.y);
}

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
	t_list	*ptr;

	if (!(map = mp_new(STDIN_FILENO)))
		return (-1);
	ft_putstr("start: ");
	show(map->start);
	ft_putstr("end: ");
	show(map->end);
	ft_putendl("Middle: ");
	ptr = map->middle;
	while (ptr)
	{
		show(*(t_room **)ptr->content);
		ptr = ptr->next;
	}
	mp_free(&map);
	return (0);
}
