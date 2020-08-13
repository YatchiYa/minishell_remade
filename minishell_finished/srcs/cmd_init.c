
#include "minishell.h"

void		add_redir_cmd(t_cmd *cmd, char *redir, char *file)
{
	t_cmd *last;

	last = last_cmd(cmd);
	last->is_rdir = 1;
	if (ft_strcmp_v2(redir, "<"))
		last->input = add_rdir(last->input, file, 0);
	else if (ft_strcmp_v2(redir, ">"))
		last->output = add_rdir(last->output, file, 0);
	else if (ft_strcmp_v2(redir, ">>"))
		last->output = add_rdir(last->output, file, 1);
}

void		add_pip_cmd(t_cmd *cmd)
{
	t_cmd *last;

	last = last_cmd(cmd);
	last->is_pipe = 1;
}

void		add_argv_cmd(t_cmd *cmd, char *arg)
{
	t_cmd	*last;
	int		cnt;
	char	**new_arr;
	int		i;

	last = last_cmd(cmd);
	cnt = wordcount_arg(last->argv);
	new_arr = malloc(sizeof(char*) * (cnt + 2));
	i = 0;
	while (i < cnt)
	{
		new_arr[i] = last->argv[i];
		i++;
	}
	new_arr[i] = ft_strdup(arg);
	new_arr[cnt + 1] = NULL;
	free(last->argv);
	last->argv = new_arr;
}

int			init_cmd(char **argv)
{
	t_minish	*minish;
	int			i;
	int			ret;

	if (!check_errors_arg(argv))
		return (0);
	minish = get_minish();
	minish->cmd = 0;
	i = 0;
	ret = 1;
	while (argv[i])
	{
		if (ret && !(ret = 0))
			minish->cmd = add_cmd(minish->cmd, argv[i]);
		else if (ft_strcmp_v2(argv[i], "|") && (ret = 1))
			add_pip_cmd(minish->cmd);
		else if (is_redir_quote(argv[i]) && (i++))
			add_redir_cmd(minish->cmd, argv[i - 1], argv[i]);
		else if (ft_strcmp_v2(argv[i], ";") && (ret = 1) && (i++))
			continue;
		else
			add_argv_cmd(minish->cmd, argv[i]);
		i++;
	}
	return (1);
}
