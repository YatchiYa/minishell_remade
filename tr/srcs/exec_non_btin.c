
#include "minishell.h"
#include "stdlib.h"
#include "stdio.h"
static char
	**create_path_arr(void)
{
	t_env	*env;
	char	*path_env;
	char	**path_arr;

	env = get_minish()->env;
	path_env = 0;
	while (env)
	{
		if (trim_queue(env->key, "PATH"))
			path_env = env->value;
		env = env->next;
	}
	if (!path_env)
		return (0);
	path_arr = ft_split(path_env, ':');
	return (path_arr);
}

static void
	free_path_arr(char **path_arr)
{
	int i;

	i = 0;
	while (path_arr[i])
	{
		free(path_arr[i]);
		i++;
	}
	free(path_arr);
}

static void
	free_tmp_env(char **env)
{
	int i;

	i = 0;
	if (env)
	{
		while (env[i])
			free(env[i++]);
		free(env);
	}
}

static void
	exec_with_path(t_cmd *cmd, char **path_arr)
{
	char	*path_cmd1;
	char	*path_cmd2;
	char	**tmp_env;
	int		i;

	i = 0;
	while (path_arr[i])
	{
		path_cmd1 = ft_strjoin(path_arr[i], "/");
		path_cmd2 = ft_strjoin(path_cmd1, cmd->argv[0]);
		tmp_env = lst_env_to_char(get_minish()->env);
		execve(path_cmd2, cmd->argv, tmp_env);
		free_tmp_env(tmp_env);
		free(path_cmd1);
		free(path_cmd2);
		i++;
	}
}

void
	exec_non_built_in(t_cmd *cmd)
{
	char	**path_arr;

	if (!handle_dollars_parse(cmd))
		exit(EXIT_FAILURE);
	set_redirect_dup2(cmd);
	if (!cmd->has_path && (path_arr = create_path_arr()))
	{
		exec_with_path(cmd, path_arr);
		free_path_arr(path_arr);
		exit(no_command_error(cmd->argv[0], 127));
	}
	else
	{
		execve(cmd->argv[0], cmd->argv, lst_env_to_char(get_minish()->env));
		exit(no_file_error(cmd->argv[0], NULL, 1));
	}
}
