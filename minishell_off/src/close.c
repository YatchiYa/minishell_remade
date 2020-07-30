#include "minishell.h"

void	ft_freestrarr(char **arr)
{
	int i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
	{
		free(arr[i]);
	}
	free(arr);
	arr = NULL;
}

void	exit_shell(void)
{
	ft_freestrarr(g_envv);
	exit(0);
}
