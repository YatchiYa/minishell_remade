#include "minishell.h"


int	ss(char c, char *delim)
{
	int	i;
	
	i = 0;
	while (delim[i])
	{
		if (delim[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ssx(char *str, char *delim)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (str[j])
	{
		i = 0;
		while (delim[i])
		{
			if (delim[i] == str[j])
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int	search_delim(char *str, char c, int n)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i] && ss(str[i], ">|<") == 0)
	{
		if (str[i] == c)
			res++;
		i++;
	}
	if (res != n)
		return (0);
	return (1);
}

void	handle_1(char *str, char c)
{
	int	i;
	char	**tab;
	int	fd;

	tab = ft_strsplit(str, c);
	i = 0;
	//while (tab[1] && *tab[1] == ' ')
	//	*tab[1]++;
	//while (tab[0] && *tab[0] == ' ')
	//	*tab[0]++;
	remove(trim_queue(tab[1]));
	fd = open(trim_queue(tab[1]), O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
	while (tab[0][i])
	{
		if (tab[0][i] != '"' && tab[0][i] != '\'')
			write(fd, &tab[0][i], 1);
		i++;
	}
	write(fd, "\n", 1);
	close(fd);
}

void	handle_2(char *str, char c)
{
	int	i;
	char	**tab;
	int	fd;
	char	*line;
	int	ret;

	tab = ft_strsplit(str, c);
	i = 0;
	//while (tab[1] && *tab[1] == ' ')
	//	*tab[1]++;
	//while (tab[0] && *tab[0] == ' ')
	//	*tab[0]++;
	fd = open(trim_queue(tab[1]), O_RDWR);
	if (fd == -1)
	{
		ft_putstr("minishell : file dons't exist : <");
		ft_putstr(tab[1]);
		ft_putstr(">\n");
		return ;
	}
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ft_strjoin(tab[0], line);
	}
	while (tab[0][i])
	{
		if (tab[0][i] != '"' && tab[0][i] != '\'')
			write(fd, &tab[0][i], 1);
		i++;
	}
	write(fd, "\n", 1);
	close(fd);
}

void	handle_3(char *str, char c)
{
	int	i;
	char	**tab;
	int	fd;
	char	*line;
	int	ret;

	tab = ft_strsplit(str, c);
	i = 0;
	//while (tab[1] && *tab[1] == ' ')
	//	*tab[1]++;
	//while (tab[0] && *tab[0] == ' ')
	//	*tab[0]++;
	fd = open(trim_queue(tab[1]), O_RDWR);
	if (fd == -1)
	{
		ft_putstr("minishell : file dons't exist : <");
		ft_putstr(tab[1]);
		ft_putstr(">\n");
		return ;
	}
	close(fd);
}

char	*ft_strchrx(char *s, char c)
{
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (NULL);
}

char	*delim_ptr(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] != '>' && str[i] != '<')
		i++;
	return (&str[i]);
}

int		handle_redirect_pwd(char *str)
{
	int			i;
	char		*res;
	char		*tmp;

	res = delim_ptr(str);
	if (res[0] == '<')
	{
		handle_3(str, '<');
		if ((tmp = ft_strchrx(res + 1, '>')) == NULL )
			handle_pwd(" ");
		else
			handle_pwd(tmp);
	}
	else if (res[0] == '>' && res[1] == '>')
	{
		handle_2(str, '>');
		if ((tmp = ft_strchrx(res + 2, '>')) != NULL || 
			(tmp = ft_strchrx(res + 2, '<')) != NULL )
			handle_pwd(tmp);
	}
	else if (res[0] == '>')
	{
		handle_1(str, '>');
		if ((tmp = ft_strchrx(res + 1, '>')) != NULL || 
			(tmp = ft_strchrx(res + 1, '<')) != NULL )
			handle_pwd(tmp);
	}
	else
	{
		ft_putstr("minishell > error argument pwd\n");
		return (1);
	}
	return (0);
}


int		handle_redirect_env(char *str)
{
	int			i;
	char		*res;
	char		*tmp;

	res = delim_ptr(str);
	if (res[0] == '<')
	{
		handle_2(str, '<');
		if ((tmp = ft_strchrx(res + 1, '>')) == NULL )
			handle_env(" ");
		else
			handle_env(tmp);
	}
	else if (res[0] == '>' && res[1] == '>')
	{
		handle_2(str, '>');
		if ((tmp = ft_strchrx(res + 2, '>')) != NULL || 
			(tmp = ft_strchrx(res + 2, '<')) != NULL )
			handle_env(tmp);
	}
	else if (res[0] == '>')
	{
		handle_1(str, '>');
		if ((tmp = ft_strchrx(res + 1, '>')) != NULL || 
			(tmp = ft_strchrx(res + 1, '<')) != NULL )
			handle_env(tmp);
	}
	else
	{
		ft_putstr("minishell > error argument pwd\n");
		return (1);
	}
	return (0);
}


int		handle_redirect_echo(char *str)
{
	int			i;
	char		*res;
	char		*tmp;
	
	if (str[0] == '>' || str[0] == '<')
		str = ft_strjoin(" ", str);
	res = delim_ptr(str);
	if (res[0] == '<')
	{
		handle_2(str, '<');
		if ((tmp = ft_strchrx(res + 1, '>')) == NULL )
			handle_echo(" ");
		else
			handle_echo(tmp);
	}
	else if (res[0] == '>' && res[1] == '>')
	{
		handle_2(str, '>');
		if ((tmp = ft_strchrx(res + 2, '>')) != NULL || 
			(tmp = ft_strchrx(res + 2, '<')) != NULL )
			handle_echo(tmp);
	}
	else if (res[0] == '>')
	{		
		handle_1(str, '>');
		if ((tmp = ft_strchrx(res + 1, '>')) != NULL || 
			(tmp = ft_strchrx(res + 1, '<')) != NULL )
			handle_echo(tmp);
	}
	else
	{
		ft_putstr("minishell > error argument pwd\n");
		return (1);
	}
	return (0);
}
