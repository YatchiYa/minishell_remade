/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:13:46 by pray              #+#    #+#             */
/*   Updated: 2020/02/21 14:13:49 by pray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_tab_non(char *builtins[8])
{
	int		i;

	i = 0;
	while (builtins[i] && i < 8)
	{
		free(builtins[i]);
		i++;
	}
}

int			is_builtin_ext(char *arg, int i)
{
	char	*builtins[8];
	char	**tmp;
	char	*key;

	key = ft_strdup(find_env(arg + 1));
	if (key != NULL && ft_strlen(key) != 0)
	{
		get_builtin(builtins);
		tmp = ft_split(key, ' ');
		while (builtins[i])
		{
			if (ft_strcmp(builtins[i], tmp[0]) == 0)
			{
				free_tab_arg(builtins);
				free_tab_arg(tmp);
				free(key);
				return (i);
			}
			i++;
		}
		free_tab_non(builtins);
		free_tab_arg(tmp);
	}
	free(key);
	return (-1);
}

void		ext_non_built(t_cmd *cmd, char **tmp)
{
	if (space_found(cmd->argv[0]) == 0 && cmd->start_dollars == 1)
	{
		tmp = ft_split(cmd->argv[0], ' ');
		tmp = tab_join(tmp, cmd->argv);
		execve(cmd->argv[0], cmd->argv, get_env_full(get_minish()->env));
		exit(no_file_error(cmd->argv[0], NULL, 1));
	}
	else
	{
		execve(cmd->argv[0], cmd->argv, get_env_full(get_minish()->env));
		exit(no_file_error(cmd->argv[0], NULL, 1));
	}
}
