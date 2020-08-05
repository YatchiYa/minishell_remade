
#include "minishell.h"

t_env		*lst_data_last(t_env *begin)
{
	while (begin->next)
		begin = begin->next;
	return (begin);
}

t_env		*lst_data_new(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

t_env		*lst_data_add(t_env *begin, char *key, char *value)
{
	t_env	*last;

	last = lst_data_last(begin);
	last->next = lst_data_new(key, value);
	return (begin);
}

char		**split_data_env(char *s)
{
	int		idx;
	int		i;
	int		j;
	char	**res;

	idx = 0;
	while (s && s[idx] != '=')
		idx++;
	res = malloc(sizeof(char*) * 2);
	res[0] = malloc(idx + 1);
	i = -1;
	while (s[++i] != '=')
		res[0][i] = s[i];
	res[0][i] = '\0';
	res[1] = malloc(ft_strlen(s) - idx);
	j = i;
	while (s[++i] != '\0')
		res[1][i - j - 1] = s[i];
	res[1][i - j - 1] = '\0';
	return (res);
}

void			init_env(char **env)
{
	char		**cut;
	int			i;
	t_minish	*minish;

	minish = get_minish();
	minish->env = 0;
	i = 0;
	while (env[i])
	{
		cut = split_data_env(env[i]);
		if (i == 0)
			minish->env = lst_data_new(cut[0], cut[1]);
		else
			lst_data_add(minish->env, cut[0], cut[1]);
		free(cut[0]);
		free(cut[1]);
		free(cut);
		i++;
	}
}
