/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pray <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:13:46 by pray             #+#    #+#             */
/*   Updated: 2020/02/21 14:13:49 by pray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			error_minishell();
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

void		close_pipe(int pipes[], int nb, int cpid[])
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

void		dup2_pipes(int pipes[], int i, int nb)
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
			dup2_pipes(pipes, i, nb);
			if ((cmd_result = is_builtin(cmd->argv[0])) != -1)
				exit(exec_builtin(cmd_result, cmd));
			exec_non_builtin(cmd);
		}
		else if (pipe_fd[i] == -1)
			error_minishell();
		cmd = cmd->next;
		i++;
	}
	close_pipe(pipes, nb, pipe_fd);
	return (cmd);
}
