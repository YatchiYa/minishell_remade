#include "minishell.h"

char		*parse_dollar(char *str)
{
	int		i;
	char	*dest;
	char	*var;

	i = -1;
	if (!(dest = malloc(sizeof(char) * (ft_strlenx(str) + 1))))
		exit_shell();
	while (str[++i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'' && str[i] != '\0')
		dest[i] = str[i];
	dest[i] = '\0';
	var = get_env_var(++dest);
	if (var == NULL)
		var = strdup(" ");
	return (var);
}