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

int			alphnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);
}

int			str_alphnum(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (alphnum(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void		split_dollar_parse(char buf_tmp[2][LINE_MAX], char *arg)
{
	int		i;
	int		j;

	buf_tmp[0][0] = arg[0];
	arg[1] == '?' ? buf_tmp[0][1] = arg[0] : 0;
	i = arg[1] == '?' ? 2 : 1;
	j = arg[1] == '?' ? 2 : 1;
	while (arg[i] && alphnum(arg[i]) == 1)
	{
		buf_tmp[0][j] = arg[i];
		i++;
		j++;
	}
	buf_tmp[0][j] = '\0';
	j = 0;
	while (arg[i])
	{
		buf_tmp[1][j] = arg[i];
		i++;
		j++;
	}
	buf_tmp[1][j] = '\0';
}

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
