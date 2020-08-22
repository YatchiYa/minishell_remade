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

void		free_tab_arg(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int			count_count_arg(char **tab)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], "\0") != 0)
			ret++;
		i++;
	}
	return (ret);
}

char		**trim_arg_cmd(char **argv)
{
	char	**tmp;
	char	*tx;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = (char**)malloc(sizeof(char*) * (count_count_arg(argv) + 1));
	while (argv[i])
	{
		tx = parse_quote_2(argv[i], -1);
		if (ft_strcmp(tx, "\0") != 0)
		{
			tmp[j] = ft_strdup(argv[i]);
			j++;
		}
		free(tx);
		i++;
	}
	tmp[j] = NULL;
	free_tab_arg(argv);
	return (tmp);
}

char		*parse_quote_2(char *argv, int i)
{
	char	buff[LINE_MAX];
	int		j;

	j = -1;
	ft_memset(buff, 0, LINE_MAX);
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
		else if (argv[i] == '~')
			i += parse_home(&argv[i], buff, &j);
		else if (argv[i] == '$')
			i += get_value_dollars_parse(&argv[i], buff, &j);
		else
			i += backslash_parse(&argv[i], buff, &j, 0);
	buff[++j] = '\0';
	return (ft_strdup(buff));
}
