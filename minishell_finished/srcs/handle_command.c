
#include "minishell.h"

void		get_signal_builtin_cmd(int status, int signo)
{
	if (signo == -1)
	{
		if (WIFEXITED(status))
			get_minish()->signal_is_called = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			get_minish()->signal_is_called = 128 + WTERMSIG(status);
	}
	else
		get_minish()->signal_is_called = signo;
}

int			is_builtin(char *arg)
{
	int		i;

	i = 0;
	while (BUILTINS[i])
	{
		if (trim_queue(BUILTINS[i], arg))
			return (i);
		i++;
	}
	return (-1);
}

int			exec_builtin(int btin_nb, t_cmd *cmd)
{
	int ret;

	ret = -1;
	if (!handle_dollars_parse(cmd))
		return (EXIT_FAILURE);
	set_redirect_dup2(cmd);
	if (btin_nb == 0)
		ret = handle_echo(cmd);
	else if (btin_nb == 1)
		ret = handle_cd(cmd);
	else if (btin_nb == 2)
		ret = handle_pwd(cmd);
	else if (btin_nb == 3)
		ret = handle_export(cmd);
	else if (btin_nb == 4)
		ret = handle_unset(cmd);
	else if (btin_nb == 5)
		ret = handle_env(cmd);
	else if (btin_nb == 6)
		ret = handle_exit(cmd);
	close_redirect_dup2(cmd);
	return (ret);
}

void		non_builtin_cmd(t_cmd *cmd)
{
	pid_t	child_pid;
	int		status;

	if ((child_pid = fork()) == -1)
		error_minishell();
	else if (child_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_non_builtin(cmd);
	}
	else if (child_pid > 0)
	{
		wait(&status);
		get_signal_builtin_cmd(status, NO_EXCODE);
	}
}

void		exec_command(void)
{
	t_cmd	*cmd;
	int		btin_nb;

	cmd = get_minish()->cmd;
	get_minish()->cmd_is_ok = 1;
	while (cmd)
	{
		if (cmd->is_pipe)
		{
			cmd = pipe_cmd_call(cmd);
			continue ;
		}
		if ((btin_nb = is_builtin(cmd->argv[0])) != -1)
			get_signal_builtin_cmd(NO_STATUS, exec_builtin(btin_nb, cmd));
		else
			non_builtin_cmd(cmd);
		cmd = cmd->next;
	}
	get_minish()->cmd_is_ok = 0;
}
