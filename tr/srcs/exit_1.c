
#include "minishell.h"

void		free_argv(void)
{
	char	**argv;
	int		i;

	argv = get_minish()->argv;
	if (argv)
	{
		i = 0;
		while (argv[i])
			free(argv[i++]);
		free(argv);
		get_minish()->argv = 0;
	}
}

void		free_line(void)
{
	if (get_minish()->line)
		free(get_minish()->line);
	get_minish()->line = NULL;
}

void		free_redirections(t_cmd *cmd)
{
	t_rdir *tmp;

	tmp = cmd->in;
	while (cmd->in)
	{
		free(cmd->in->file);
		tmp = cmd->in->next;
		free(cmd->in);
		cmd->in = tmp;
	}
	tmp = cmd->out;
	while (cmd->out)
	{
		free(cmd->out->file);
		tmp = cmd->out->next;
		free(cmd->out);
		cmd->out = tmp;
	}
}

void		free_1(void)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	int		i;

	free_line();
	free_argv();
	cmd = get_minish()->cmd;
	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->argv)
		{
			i = -1;
			while (cmd->argv[++i])
				free(cmd->argv[i]);
			free(cmd->argv);
		}
		free_redirections(cmd);
		free(cmd);
		cmd = tmp;
	}
	get_minish()->cmd = 0;
}

void		free_env(void)
{
	t_env *env;
	t_env *tmp;

	env = get_minish()->env;
	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}
