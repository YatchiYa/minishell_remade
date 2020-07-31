#include "minishell.h"

int			check_arg(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			return (1);
		else if (str[i] > 0 && str[i] < 127 && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int				handle_pwd(char *str)
{
	char	*cwd;
	char	*buff;

	if (!(buff = malloc(sizeof(char) * 4097)))
		return 1;
	cwd = getcwd(buff, 4096);
	if (str == NULL)
	{
		ft_putstr(cwd);
		ft_putstr("\n");
		free(buff);
	}
	else if (check_arg(str) == 0)
	{
		ft_putstr("pwd : error too many argument \n");
		return (1);
	}
	else if (ssx(str, "><") == 1)
	{
		cwd = ft_strjoin(cwd, " ");
		str = ft_strjoin(cwd, str);
		return (handle_redirect_pwd(str));
	}
	else
	{
		ft_putstr(cwd);
		ft_putstr("\n");
		free(buff);
	}
	return (0);
}

en_status           bultinPWD(char   **words)
{
    int rval = handle_pwd(words[1]);
    if(rval == 0)
        return STATUS_SUCCESS;
    return STATUS_SOFT_FAILURE;
}