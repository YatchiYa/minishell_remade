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

char		*ft_split_arguments_extends(char *line, int index,
				int start, int count)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!ft_is_sep_space(SEP_SPACE, line[i]) && line[i] && ++count)
		{
			while (!ft_is_sep_space(SEP_SPACE, line[i]) && line[i])
				i = trim_quote(line, i) + 1;
			if (count == index)
				return (ft_strsub(line, start, i - start));
			start = i;
		}
		if (ft_is_sep_space(SEP, line[i]) && ++count)
			if (count == index)
			{
				return (ft_strsub(line, start,
						i + check_sep(line, i, 1) - start));
			}
		i += check_sep(line, i, 2);
		start = i;
	}
	return (NULL);
}

char		**ft_split_arguments(char *line)
{
	char	**argv;
	int		count;
	int		i;

	i = -1;
	count = word_str_count(line);
	if (!(argv = (char **)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	while (++i < count)
		argv[i] = ft_split_arguments_extends(line, i + 1, 0, 0);
	argv[i] = NULL;
	return (argv);
}

int			previous_line_is_eof(void)
{
	char		*previous_line;
	char		*new_line;
	t_minish	*minish;

	minish = get_minish();
	new_line = 0;
	if ((minish->ret = get_next_line(0, &new_line)) < 0)
		error_minishell();
	previous_line = minish->is_end_of_file ? minish->line : "";
	if (!(minish->line = ft_strjoin(previous_line, new_line)))
		error_minishell();
	if (minish->is_end_of_file)
		free(previous_line);
	free(new_line);
	if (minish->ret > 0)
		minish->is_end_of_file = 0;
	if (minish->ret == 0)
	{
		ft_putstr("\n");
		return (0);
	}
	return (1);
}

int			current_line(void)
{
	t_minish	*minish;

	minish = get_minish();
	if ((minish->ret = get_next_line(0, &(minish->line))) == -1)
		error_minishell();
	if ((minish->ret == 0 && ft_strlen(minish->line)))
	{
		minish->is_end_of_file = 1;
		ft_putstr("\n");
		return (0);
	}
	if (minish->ret == 0 && !ft_strlen(minish->line))
	{
		ft_putstr("\n");
		eof_exit();
	}
	return (1);
}

int			ft_getline(void)
{
	t_minish	*minish;

	minish = get_minish();
	if (minish->is_end_of_file)
	{
		if (!previous_line_is_eof())
			return (0);
	}
	else
	{
		if (!current_line())
			return (0);
	}
	minish->argv = ft_split_arguments(minish->line);
	if (!minish->argv)
		error_minishell();
	return (1);
}
