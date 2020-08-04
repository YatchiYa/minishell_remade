
#include "minishell.h"

char		*ft_strdup(const char *s1)
{
	size_t	i;
	char	*ret;

	if (!s1)
		return (0);
	if (!(ret = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (0);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char		*ft_strchr(const char *s, int c)
{
	char	*ret;

	ret = (char*)s;
	while (*ret != c)
	{
		if (*ret == '\0')
			return (0);
		ret++;
	}
	return (ret);
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
	new->in = NULL;
	new->out = NULL;
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
