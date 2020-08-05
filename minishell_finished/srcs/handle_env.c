
#include "minishell.h"

void		printenv(t_env *env)
{
	while (env)
	{
		if (env->value != NULL)
		{
			ft_putstr(env->key);
			ft_putstr("=");
			ft_putstr(env->value);
			ft_putstr("\n");
		}
		env = env->next;
	}
}

int			handle_env(t_cmd *cmd)
{
	(void)cmd;
	printenv(get_minish()->env);
	return (EXIT_SUCCESS);
}
