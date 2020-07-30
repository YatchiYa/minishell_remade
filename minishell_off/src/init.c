#include "minishell.h"

void			init_envv(int ac, char **av, char **envv)
{
	int		i;
	
	g_envv = (char **)ft_memalloc(sizeof(char *) * (envv_len(envv) + 1));
	i = -1;
	while (envv[++i])
	{
		if (!(g_envv[i] = strdup(envv[i])))
			exit_shell();
	}
	g_envv[i] = NULL;
}
