#include "minishell.h"

char	**realloc_envv(int new_size)
{
	char	**new;
	int		i;

	new = (char **)ft_memalloc(sizeof(char *) * (new_size + 1));
	i = -1;
	while (g_envv[++i] && i < new_size)
	{
		new[i] = strdup(g_envv[i]);
		free(g_envv[i]);
	}
	free(g_envv);
	return (new);
}

char	*get_env_var(char *var)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_envv[++i])
	{
		tmp = ft_strjoinch(var, '=');
		if (ft_strstartswith(g_envv[i], tmp))
		{
			free(tmp);
			return (ft_strchr(g_envv[i], '=') + 1);
		}
		free(tmp);
	}
	return (NULL);
}

int		find_env_var(char *var)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_envv[++i])
	{
		tmp = ft_strjoinch(var, '=');
		if (ft_strstartswith(g_envv[i], tmp))
		{
			free(tmp);
			return (i);
		}
		free(tmp);
	}
	return (i);
}

void	set_env_var(char *key, char *value)
{
	int		pos;
	char	*tmp;

	pos = find_env_var(key);
	tmp = ft_strjoin("=", value);
	ctrld = 0;
	if (g_envv[pos])
	{
		free(g_envv[pos]);
		if (value)
			g_envv[pos] = ft_strjoin(key, tmp);
		else
			g_envv[pos] = ft_strjoin(key, "=");
	}
	else
	{
		g_envv = realloc_envv(pos + 1);
		if (value)
			g_envv[pos] = ft_strjoin(key, tmp);
		else
			g_envv[pos] = ft_strjoin(key, "=");
	}
	free(tmp);
}
