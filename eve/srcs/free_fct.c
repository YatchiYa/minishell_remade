/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarab <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:13:46 by yarab             #+#    #+#             */
/*   Updated: 2020/02/21 14:13:49 by yarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	tmp = cmd->input;
	while (cmd->input)
	{
		free(cmd->input->file_io);
		tmp = cmd->input->next;
		free(cmd->input);
		cmd->input = tmp;
	}
	tmp = cmd->output;
	while (cmd->output)
	{
		free(cmd->output->file_io);
		tmp = cmd->output->next;
		free(cmd->output);
		cmd->output = tmp;
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
			while (cmd->argv && cmd->argv[++i] && cmd->argv[i])
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
