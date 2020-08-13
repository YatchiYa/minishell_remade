
#include "minishell.h"

t_env		*last_data(t_env *begin)
{
	while (begin->next)
		begin = begin->next;
	return (begin);
}

t_env		*new_data(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

t_env		*add(t_env *begin, char *key, char *value)
{
	t_env	*last;

	last = last_data(begin);
	last->next = new_data(key, value);
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
	char		**tmp;
	int			i;
	t_minish	*minish;

	minish = get_minish();
	minish->env = 0;
	i = 0;
	while (env[i])
	{
		tmp = split_data_env(env[i]);
		if (i == 0)
			minish->env = new_data(tmp[0], tmp[1]);
		else
			add(minish->env, tmp[0], tmp[1]);
		free(tmp[0]);
		free(tmp[1]);
		free(tmp);
		i++;
	}
}
