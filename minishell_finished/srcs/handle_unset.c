
#include "minishell.h"

void		remove_data(char *key)
{
	t_env *prev;
	t_env *tmp;
	t_env *next;

	prev = 0;
	tmp = get_minish()->env;
	while (tmp)
	{
		next = tmp->next;
		if (trim_queue(tmp->key, key))
		{
			if (prev)
				prev->next = next;
			else
				get_minish()->env = next;
			free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = next;
	}
}

int			handle_unset(t_cmd *cmd)
{
	int i;

	i = 1;
	while (cmd->argv[i])
	{
		remove_data(cmd->argv[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
