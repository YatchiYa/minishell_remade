
#include "minishell.h"

void		handle_touch(char *str)
{
	int	fd;

	fd = open(str, O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
	close(fd);
}

void		handle_rm(char *str)
{
	remove(str);
}
