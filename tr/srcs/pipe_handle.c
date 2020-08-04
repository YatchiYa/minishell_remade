
#include "minishell.h"

int			nb_pipes(t_cmd *cmd_list)
{
	int i;

	i = 0;
	while (cmd_list)
	{
		if (cmd_list->is_pipe)
			i++;
		else
			break ;
		cmd_list = cmd_list->next;
	}
	return (i);
}

int			init_pipes(int pipes[], int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		if (pipe(pipes + (i * 2)) == -1)
			fatal_error_exit();
		i++;
	}
	return (1);
}

void		close_all(int pipes[], int nb)
{
	int i;

	i = 0;
	while (i < 2 * nb)
		close(pipes[i++]);
}

void		close_pipe_and_wait(int pipes[], int nb, int cpid[])
{
	int status;
	int	i;
	
	close_all(pipes, nb);
	i = 0;
	while (i < nb + 1)
	{
		waitpid(cpid[i], &status, 0);
		i++;
	}
	get_signal_builtin_cmd(status, NO_EXCODE);
}

void		set_dups_call(int pipes[], int i, int nb)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (i < nb)
		dup2(pipes[i * 2 + 1], 1);
	if (i > 0)
		dup2(pipes[(i - 1) * 2], 0);
	close_all(pipes, nb);
}

t_cmd		*pipe_cmd_call(t_cmd *cmd)
{
	int pipes[nb_pipes(cmd) * 2];
	int nb;
	int i;
	int cmd_result;
	int pipe_fd[nb_pipes(cmd) + 1];

	nb = nb_pipes(cmd);
	if (!init_pipes(pipes, nb))
		return (0);
	i = 0;
	while (i < (nb + 1))
	{
		if ((pipe_fd[i] = fork()) == 0)
		{
			set_dups_call(pipes, i, nb);
			if ((cmd_result = is_builtin(cmd->argv[0])) != -1)
				exit(exec_builtin(cmd_result, cmd));
			exec_non_built_in(cmd);
		}
		else if (pipe_fd[i] == -1)
			fatal_error_exit();
		cmd = cmd->next;
		i++;
	}
	close_pipe_and_wait(pipes, nb, pipe_fd);
	return (cmd);
}
