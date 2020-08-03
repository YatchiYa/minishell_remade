#include "minishell.h"

int		cd_simple(char *path)
{
	char	*cwd;
	int		i;
	char	buff[4097];

	cwd = getcwd(buff, 4096);
	i = 0;
	while (path[i] == ' ')
		i++;
	path = path + i;
	if (only_point(path) == 1 && ft_strlenx(path) > 2)
	{
		ft_putstr("cd: ");
		ft_putstr(path);
		ft_putstr(" not a directory \n");
		return (1);
	}
	else if (!chdir(path))
	{
		set_env_var("OLDPWD", cwd);
		return (0);
	}
	else
	{
		ft_putstr("cd: ");
		if (access(path, F_OK) == -1)
			ft_putstr("no such file or directory: ");
		else if (access(path, R_OK) == -1)
			ft_putstr("permission denied: ");
		else
			ft_putstr("not a directory: ");
		ft_putstr(path);
		ft_putstr("\n");
		return (1);
	}
}

int		cd_complex(void)
{
	char	*cwd;
	int		i;
	int		ret;
	int		xet;
	char	buff[4097];
	char	*dest;
	
	cwd = getcwd(buff, 4096);
	if (!(dest = malloc(sizeof(char) * (ft_strlenx(cwd) + 1))))
		exit_shell();
	ret = 0;
	i = 0;
	while(cwd[i])
	{
		if (cwd[i] == '\\')
			ret++;
		i++;
	}
	i = 0;
	xet = 0;
	while (cwd[i] && xet < ret)
	{
		if (cwd[i] == '\\')
			xet++;
		dest[i] = cwd[i];
		i++;
	}
	dest[i] = '\0';
	return (cd_simple(dest));
}

int		cd_handle_home(void)
{
	char	*cwd;

	cwd = get_env_var("HOME");
	return (cd_simple(cwd));
}

int		handle_cdx(char *path)
{
	char	*str;
	char	**tab;

	while (*path == ' ')
		path++;
	tab = ft_split(path, " ");
	if ((strcmp(path, "\0") == 0 || strcmp(path, "~") == 0 || strcmp(path, "--") == 0))
		cd_handle_home();
	else if (path[0] == '$')
		return (cd_simple(parse_dollar(path)));
	else if (strcmp(path, "-") == 0)
	{
		str = g_envv[find_env_var("OLDPWD")];
		while (*str != '=')
			str++;
		if (strcmp(++str, " ") == 0)
			ft_putstr("minishell : OLDPWD not defined \n");
		else
			return (cd_simple(str));
	}
	else if (strcmp(tab[1], "..") == 0)
		return (cd_complex());
	else if (strcmp(tab[1], ".") == 0)
		;
	else
		return (cd_simple(path));
	return (0);
}

int		handle_cd_x(char *dest, char *str)
{
	char	**tab;

	tab = split_commande(dest);
	if (((str[0] == '"' || str[0] == '\'') && (str[1] == ' ' || str[1] == '\0'))
		|| ((str[ft_strlenx(str)] == '"' || str[ft_strlenx(str)] == '\'') && (str[ft_strlenx(str) - 1] == ' ' || str[ft_strlenx(str) - 1] == '\0')))
	{
		ft_putstr("command error :");   
		ft_putstr(str);
		return (0);
	}
	else
	{
		str = str[0] == '"' || str[0] == '\'' ?
		ft_substr(str, 1, ft_strlenx(str) - 2) : ft_substr(str, 0, ft_strlenx(str));
		str = ft_strjoin(" ", str);
		str = ft_strjoin(tab[0], str);
		int	i = -1;
		char	*newPat;

		newPat = malloc(sizeof(char) * (ft_strlenx(str) + 1));
		while (str[++i] != ' ')
				newPat[i] = str[i];
		newPat[i] = '\0';
		return (handle_cdx(newPat));
	}
}

int		handle_cd(char *str)
{
    char	*dest;
    int		ret;
	int		xet;
	
	if (str == NULL)
		return (cd_handle_home());
	dest = trim_quote(str, &ret, &xet);
	if (ret % 2 != 0 && ret != 0)
	{
		ft_putstr("minishell > error parse quote \n");
		return (1);
	}
	else if (xet % 2 != 0 && xet != 0)
	{
		ft_putstr("minishell > error parse quote \n");
		return (1);
	}
	else
		return (handle_cd_x(dest, str));
}
