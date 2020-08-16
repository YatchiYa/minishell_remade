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

void		display_echo(char **argv, int i, int cnt)
{
	while (argv[i])
	{
		ft_putstr(argv[i]);
		if (i < cnt - 1)
			ft_putstr(" ");
		i++;
	}
}

int			index_echo_display(char **argv, int i)
{
	while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
		i++;
	return (i);
}

int			handle_echo(t_cmd *cmd)
{
	int cnt;
	int	index;

	cnt = count_arg(cmd->argv);
	if (cnt >= 2 && ft_strcmp(cmd->argv[1], "-n") == 0)
	{
		index = index_echo_display(cmd->argv, 1);
		display_echo(cmd->argv, index, cnt);
	}
	else
	{
		display_echo(cmd->argv, 1, cnt);
		ft_putstr("\n");
	}
	return (EXIT_SUCCESS);
}
