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

void	free_tab(char *str[8])
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
}

void	display(char *cwd, int i)
{
	char		*tmp;

	cwd = ft_strsub(cwd, i, ft_strlen(cwd));
	tmp = ft_strjoin("~", cwd);
	ft_putstr(" \033[31m");
	ft_putstr(tmp);
	ft_putstr("\033[0m");
	ft_putstr("\033[32m");
	ft_putstr("$ ");
	ft_putstr("\033[0m");
	free(cwd);
	free(tmp);
}

void	display_ext(int ret, char *cwd, int i)
{
	if (ret < 3)
	{
		ft_putstr(" \033[31m");
		ft_putstr(cwd);
		ft_putstr("\033[0m");
		ft_putstr("\033[32m");
		ft_putstr("$ ");
		ft_putstr("\033[0m");
	}
	else
		display(cwd, i);
}

void	display_prompt_msg(void)
{
	char	cwd[PATH_MAX];
	int		ret;
	int		i;

	getcwd(cwd, 4096);
	ret = 0;
	i = 0;
	while (cwd[i] && ret < 3)
	{
		if (cwd[i] == '/')
			ret++;
		i++;
	}
	display_ext(ret, cwd, i);
}
