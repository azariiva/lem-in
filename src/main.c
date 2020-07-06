#include "libam.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int		main(void)
{
	t_am	*am;

	if (!(am = am_new(STDIN_FILENO)))
		return (-1);
	am_show(am);
	am_del(&am);
	return (0);
}
