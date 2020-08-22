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

int			get_value_dollars_parse_2(char *arg, char *buff, int *j)
{
	char	key[100];
	char	*value;
	char	*tmp;
	int		ret;
	char	buf_tmp[2][LINE_MAX];

	ret = 0;
	split_dollar_parse(buf_tmp, arg);
	if (*arg == '$' && *(arg + 1) == '?')
	{
		ret = 1;
		tmp = ft_itoa(get_minish()->signal_is_called);
		*j = ft_strlcat(buff, tmp, LINE_MAX) - 1;
		free(tmp);
	}
	else if (*arg == '$' && (!*(arg + 1) || *(arg + 1) == ' '))
		buff[++*j] = *arg;
	else
	{
		tmp = buf_tmp[0];
		ret = get_env_data(key, ++tmp);
		value = find_env(key);
		*j = ft_strlcat(buff, value, LINE_MAX) - 1;
	}
	return (ret);
}

void		trrm(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	tmp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[++i])
		tmp[i] = str[i];
	tmp[i] = '\0';
	i = -1;
	j = -1;
	while (tmp[++i])
	{
		if (ft_is_sep_space(SEP, tmp[i]) && tmp[i])
		{
			str[++j] = '"';
			str[++j] = tmp[i];
			str[++j] = '"';
		}
		else
			str[++j] = tmp[i];
	}
	str[++j] = '\0';
	free(tmp);
}

char		*parse_quote_3(char *argv, int i)
{
	char	buff[LINE_MAX];
	int		j;

	j = -1;
	ft_memset(buff, 0, LINE_MAX);
	if (argv[0] == '$')
	{
		i += get_value_dollars_parse_2(&argv[0], buff, &j);
		trrm(buff);
		if (ft_strlen(buff) == 0)
			return (argv);
	}
	else
	{
		while (argv[++i])
			buff[++j] = argv[i];
	}
	buff[++j] = '\0';
	free(argv);
	return (ft_strdup(buff));
}
