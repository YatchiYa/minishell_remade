#include "minishell.h"

void		handle_unset(char *str)
{
	int		i;
	int		index;
	char	**tab;

	i = 0;
	while (*str == ' ')
		str++;
	tab = ft_strsplit(str, ' ');
	while (tab[i])
	{
		index = 0;
		index = find_env_var(tab[i]);
		remove_env_var(index);
		i++;
	}
}