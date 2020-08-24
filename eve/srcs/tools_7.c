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

char		**tab_join(char **tab, char **argv)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = (char**)malloc(sizeof(char*) * (count_arg(tab)
			+ count_arg(argv) + 1));
	i = -1;
	j = -1;
	while (tab[++i])
		tmp[++j] = ft_strdup(tab[i]);
	i = 0;
	while (argv[++i])
		tmp[++j] = ft_strdup(argv[i]);
	tmp[++j] = NULL;
	free_tab_arg(tab);
	return (tmp);
}

void		execrrr(t_cmd *cmd, char **path_arr)
{
	int		i;
	char	**tmp;
	char	*path;
	char	**g_envp;
	char	*path_extend;

	i = 0;
	tmp = ft_split(cmd->argv[0], ' ');
	tmp = tab_join(tmp, cmd->argv);
	while (path_arr[i])
	{
		path = ft_strjoin(path_arr[i], "/");
		path_extend = ft_strjoin(path, tmp[0]);
		g_envp = get_env_full(get_minish()->env);
		execve(path_extend, tmp, g_envp);
		free_env_2(g_envp);
		free(path);
		free(path_extend);
		i++;
	}
	free_tab_arg(tmp);
}

void		get_builtin(char *builtins[8])
{
	builtins[0] = ft_strdup("echo");
	builtins[1] = ft_strdup("cd");
	builtins[2] = ft_strdup("pwd");
	builtins[3] = ft_strdup("export");
	builtins[4] = ft_strdup("unset");
	builtins[5] = ft_strdup("env");
	builtins[6] = ft_strdup("exit");
	builtins[7] = NULL;
}

int			ext(char *argv, char buff[LINE_MAX], int *j, int k)
{
	int		i;

	i = k;
	if (argv[i] == '~')
		i += parse_home(&argv[i], buff, j);
	else if (argv[i] == '$')
		i += get_value_dollars_parse(&argv[i], buff, j);
	else
		i += backslash_parse(&argv[i], buff, j, 0);
	return (i);
}

char		*parse_quote_q(char *argv, int i, t_cmd *cmd)
{
	char	buff[LINE_MAX];
	int		j;

	j = -1;
	ft_memset(buff, 0, LINE_MAX);
	if (argv[0] == '$')
		cmd->start_dollars = 1;
	while (argv[++i])
		if (argv[i] == '\'')
			while (argv[++i] != '\'')
				buff[++j] = argv[i];
		else if (argv[i] == '\"')
			while (argv[++i] != '\"')
				if (argv[i] == '$')
					i += get_value_dollars_parse(&argv[i], buff, &j);
				else
					i += backslash_parse(&argv[i], buff, &j, 1);
		else if (argv[0] == '#')
			return (NULL);
		else
			i = ext(argv, buff, &j, i);
	buff[++j] = '\0';
	return (ft_strdup(buff));
}
