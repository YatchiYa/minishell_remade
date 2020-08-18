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

int		count_arg(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

char	*find_env(char *key)
{
	t_env	*env;

	env = get_minish()->env;
	while (env)
	{
		if (ft_strcmp_v2(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int		handle_pwd(t_cmd *cmd)
{
	char cwd[PATH_MAX];

	(void)cmd;
	if (!(getcwd(cwd, sizeof(cwd))))
	{
		ft_putstr("normal shell : ");
		ft_putstr(find_env("PWD"));
		ft_putstr("/.\n but ");
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (EXIT_FAILURE);
	}
	ft_putstr(cwd);
	ft_putstr("\n");
	return (EXIT_SUCCESS);
}
