#include "minishell.h"

void	display(char *cwd, int i)
{
	cwd = ft_substr(cwd, i, ft_strlenx(cwd));
	cwd = ft_strjoin("~", cwd);
	ft_putstr(" \033[31m");
	ft_putstr(cwd);
	ft_putstr("\033[0m");
	ft_putstr("\033[32m");
	ft_putstr("$ ");
	ft_putstr("\033[0m");
}

void	display_prompt_msg(void)
{
	char	*cwd;
	char	*buff;
	char	*parsed_cwd;
	int		ret;
	int		i;

	if (!(buff = malloc(sizeof(char) * 4097)))
		return ;
	cwd = getcwd(buff, 4096);
	ret = 0;
	i = 0;
	while (cwd[i]  && ret < 3)
	{
		if (cwd[i] == '/')
			ret++;
		i++;
	}
	if (ret < 3)
	{
		ft_putstr(" \033[31m");
		ft_putstr(cwd);
		ft_putstr("\033[0m");
		ft_putstr("\033[32m");
		ft_putstr("$ ");
		ft_putstr("\033[0m");
	}
	else
		display(cwd, i);
	free(buff);
}
