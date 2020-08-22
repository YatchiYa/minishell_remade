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

int			get_env_data(char key[], char *arg)
{
	int i;

	i = 0;
	while (arg[i] && !ft_is_sep_space(" $\"\'=\\", arg[i]))
	{
		key[i] = arg[i];
		i++;
	}
	key[i] = '\0';
	return (i);
}

int			get_value_dollars_parse(char *arg, char *buff, int *j)
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

int			backslash_parse(char *arg, char *buff, int *j, int quotes)
{
	int ret;

	ret = 0;
	if (*arg == '\\' && quotes)
	{
		ret = 1;
		if (ft_is_sep_space("$\'\"\\", arg[1]))
			buff[++*j] = *(++arg);
		else
		{
			buff[++*j] = *arg;
			buff[++*j] = *(++arg);
		}
	}
	else if (*arg == '\\')
	{
		ret = 1;
		buff[++*j] = *(++arg);
	}
	else
		buff[++*j] = *arg;
	return (ret);
}

char		*parse_quote(char *argv, int i)
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
		else if (argv[0] == '#')
			return (NULL);
		else
			i += backslash_parse(&argv[i], buff, &j, 0);
	buff[++j] = '\0';
	return (ft_strdup(buff));
}

int			handle_dollars_parse(t_cmd *cmd, int i)
{
	char	*old_arg;

	while (cmd->argv[++i])
	{
		old_arg = cmd->argv[i];
		cmd->argv[i] = parse_quote(cmd->argv[i], -1);
		free(old_arg);
	}
	if (get_minish()->input_first == 1)
	{
		if (!check_input(cmd->input))
			return (0);
		if (!check_output(cmd->output))
			return (0);
	}
	if (get_minish()->output_first == 1)
	{
		if (!check_output(cmd->output))
			return (0);
		if (!check_input(cmd->input))
			return (0);
	}
	return (1);
}
