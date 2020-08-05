
#include "minishell.h"

int			exec_old_path(char *path)
{
	char	*old;

	old = find_env("OLDPWD");
	if ((old) != NULL && ft_strlen(old) > 0)
	{
		if (chdir(old) == -1)
		{
			ft_putstr("error OLDPWD");
			return (-1);
		}
		add_data("OLDPWD", path);
	}
	else
	{
		ft_putstr("minishell : OLDPWD not defined \n");
		return (0);
	}
	return (EXIT_SUCCESS);
}

int			extends_cd(t_cmd *cmd, char *path)
{
	char		*value;

	if (trim_queue(cmd->argv[1], "/"))
		value = ft_strdup("/");
	else if (trim_queue(cmd->argv[1], "--"))
		value = find_env("HOME");
	else if (trim_queue(cmd->argv[1], "~"))
		value = find_env("HOME");
	else
		value = cmd->argv[1];
	if (chdir(value) == -1)
		return (no_file_error(cmd->argv[0], cmd->argv[1], EXIT_FAILURE));
	add_data("OLDPWD", path);
	return (EXIT_SUCCESS);
}

int			handle_cd(t_cmd *cmd)
{
	char	cwd[PATH_MAX];
	int		cnt;
	char	*value;
	char	*path;
	
	cnt = count_arg(cmd->argv);
	path = getcwd(cwd, sizeof(cwd));
	if (cnt == 1)
	{
		value = find_env("HOME");
		chdir(value);
		add_data("OLDPWD", path);
	}
	else if (cnt > 3)
		return (too_many_arg_error(cmd->argv[0], EXIT_FAILURE));
	else if (ft_strlen(cmd->argv[1]) > PATH_MAX)
		return (file_too_long(cmd->argv[0], cmd->argv[1], EXIT_FAILURE));
	else if (trim_queue(cmd->argv[1], "-"))
		return (exec_old_path(path));
	else
		return (extends_cd(cmd, path));
	return (EXIT_SUCCESS);
}
