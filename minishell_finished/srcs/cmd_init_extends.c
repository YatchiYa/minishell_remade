
#include "minishell.h"

int			check_errors_arg(char **argv)
{
	if (is_redirections(argv)
		&& is_pipe(argv)
		&& is_point_virgule(argv))
		return (1);
	return (0);
}

int			wordcount_arg(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

t_cmd		*create_cmd(char *data)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	new->argv = malloc(sizeof(char*) * 2);
	new->argv[0] = ft_strdup(data);
	new->argv[1] = NULL;
	new->is_pipe = 0;
	new->is_rdir = 0;
	if (ft_strchr(new->argv[0], '/'))
		new->has_path = 1;
	else
		new->has_path = 0;
	new->input = NULL;
	new->output = NULL;
	new->next = NULL;
	return (new);
}

t_cmd		*add_cmd(t_cmd *begin, char *data)
{
	t_cmd	*tmp;

	if (!begin)
		return (create_cmd(data));
	else
	{
		tmp = begin;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_cmd(data);
	}
	return (begin);
}

t_cmd		*last_cmd(t_cmd *cmd)
{
	t_cmd	*last;

	last = cmd;
	while (last->next)
		last = last->next;
	return (last);
}
