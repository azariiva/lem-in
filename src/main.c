
#include "libway.h"
#include "algo.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int		main(void)
{
	t_am	*am;

	if (!(am = am_new(STDIN_FILENO)))
		return (-1);
	if (find_shortest(am) != OK)
	{
		ft_putendl_fd("ERROR", STDERR_FILENO);
		am_del(&am);
		return (-1);
	}
	while (find_shortest(am) == OK)
		;
	ft_printf("\n");
	if (run_ants(am) == ERR)
	{
		am_del(&am);
		return (-1);
	}
	am_del(&am);
	return (0);
}
