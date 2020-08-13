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

void	display(char *cwd, int i)
{
	cwd = ft_strsub(cwd, i, ft_strlen(cwd));
	cwd = ft_strjoin("~", cwd);
	ft_putstr(" \033[31m");
	ft_putstr(cwd);
	ft_putstr("\033[0m");
	ft_putstr("\033[32m");
	ft_putstr("$ ");
	ft_putstr("\033[0m");
}

void	display_prompt_msg(void)
{
	char	*cwd;
	char	*buff;
	int		ret;
	int		i;

	if (!(buff = malloc(sizeof(char) * 4097)))
		return ;
	cwd = getcwd(buff, 4096);
	ret = 0;
	i = 0;
	while (cwd[i]  && ret < 3)
	{
		if (cwd[i] == '/')
			ret++;
		i++;
	}
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
	free(buff);
}
