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
	get_minish()->comment_found = 0;
	while (argv[i])
	{
		ft_putstr(argv[i]);
		if (i < cnt - 1 && ft_strlen(argv[i]) != 0)
			ft_putstr(" ");
		i++;
	}
}

int			spec_check_only_n(char *str)
{
	unsigned int		i;

	if (str[0] != '-')
		return (0);
	else if (str[0] == '-' && str[1] && str[1] != 'n')
		return (0);
	else if (str[0] == '-' && str[1])
	{
		i = 1;
		while (str[i] == 'n')
			i++;
		if (i == ft_strlen(str))
			return (1);
		else
			return (0);
	}
	return (0);
}

int			index_echo_display(char **argv, int i)
{
	while (argv[i] && spec_check_only_n(argv[i]) == 1)
		i++;
	return (i);
}

int			handle_echo(t_cmd *cmd)
{
	int		cnt;
	int		index;
	char	**tmp;

	tmp = ft_split(cmd->argv[0], ' ');
	tmp = tab_join(tmp, cmd->argv);
	cnt = count_arg(tmp);
	if (cnt >= 2 && spec_check_only_n(tmp[1]) != 0)
	{
		index = index_echo_display(tmp, 1);
		display_echo(tmp, index, cnt);
	}
	else
	{
		display_echo(tmp, 1, cnt);
		ft_putstr("\n");
	}
	free_tab_arg(tmp);
	return (EXIT_SUCCESS);
}
