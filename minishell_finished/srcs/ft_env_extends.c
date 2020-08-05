
#include "minishell.h"

int				ft_envlen(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		if (env->value)
			i++;
		env = env->next;
	}
	return (i);
}

char			**get_env_full(t_env *env)
{
	char	**res;
	char	*tmp;
	int		i;

	if (!(res = malloc(sizeof(char*) * (ft_envlen(env) + 1))))
		return (NULL);
	i = 0;
	while (env)
	{
		if (!env->value)
		{
			env = env->next;
			continue ;
		}
		tmp = ft_strjoin(env->key, "=");
		res[i++] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
	}
	res[i] = 0;
	return (res);
}
