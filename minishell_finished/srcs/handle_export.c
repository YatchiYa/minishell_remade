
#include "minishell.h"

void		add_data(char *key, char *value)
{
	t_env	*env;
	t_env	*last;

	env = get_minish()->env;
	while (env)
	{
		if (ft_strcmp_v2(env->key, key))
		{
			if (env->value && value)
				free(env->value);
			if (value)
				env->value = ft_strdup(value);
			return ;
		}
		last = env;
		env = env->next;
	}
	last->next = new_data(key, value);
}

void		printf_env_export(t_env *env)
{
	while (env)
	{
		ft_putstr(env->key);
		if (env->value != NULL)
		{
			ft_putstr("=");
			ft_putstr(env->value);
		}
		ft_putstr("\n");
		env = env->next;
	}
}

int			error_handle_export(char *data)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(data, 2);
	ft_putstr_fd("': not a valid identifier", 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}

void		check_arg_and_export(t_cmd *cmd, int i, int *ret)
{
	int end;
	int tmp;

	end = 0;
	tmp = 1;
	if (cmd->argv[i][0] == '\0')
		*ret = error_handle_export(cmd->argv[i]);
	else if (ft_strchr(cmd->argv[i], '='))
	{
		if (cmd->argv[i][0] == '=' && !(tmp = 0))
			*ret = error_handle_export(cmd->argv[i]);
		while (cmd->argv[i][end] != '=')
			if (ft_is_sep_space("\"\' ", cmd->argv[i][end++]) && !(tmp = 0))
			{
				*ret = error_handle_export(cmd->argv[i]);
				break ;
			}
		if (tmp)
		{
			cmd->argv[i][end] = '\0';
			add_data(cmd->argv[i], &cmd->argv[i][++end]);
		}
	}
	else
		add_data(cmd->argv[i], NULL);
}

int			handle_export(t_cmd *cmd)
{
	int i;
	int ret;

	i = 0;
	ret = EXIT_SUCCESS;
	if (!cmd->argv[1])
		printf_env_export(get_minish()->env);
	while (cmd->argv[++i])
		check_arg_and_export(cmd, i, &ret);
	return (ret);
}
