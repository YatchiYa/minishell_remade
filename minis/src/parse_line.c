#include "minishell.h"

void	extendx(char *str, char c)
{
	int		i;
	char	*line;

	i = 0;
	while (str[ft_strlenx(str) - 1] != c && calc_c(str, c) % 2 != 0)
	{
		line = NULL;
		ft_putstr("quote > ");
		get_next_line(0, &line);
		str = ft_strjoin(str, "\\n");
		str = ft_strjoin(str, line);
	}
    ft_putstr("Minishell : commande not found");   
    ft_putstr(str);
    ft_putstr("\n");
}

char		*trim_str(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = malloc(sizeof(char) * (ft_strlenx(str + 1)));

	i = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] != '"' && str[j] != '\'')
		{
			tmp[i] = str[j];
			i++;
		}
		j++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char		*trim_parse_ex(char *dest, char *str)
{
	char	**tab;
	
	tab = split_commande(dest);
	if (((tab[0][0] == '"' || tab[0][0] == '\'') && (tab[0][1] == ' ' || tab[0][1] == '\0'))
		|| ((tab[0][ft_strlenx(tab[0])] == '"' || tab[0][ft_strlenx(tab[0])] == '\'') && (tab[0][ft_strlenx(tab[0]) - 1] == ' ' || tab[0][ft_strlenx(tab[0]) - 1] == '\0')))
	{
		ft_putstr("command error :");   
		ft_putstr(tab[0]);
		return (NULL);
	}
	else
	{
		char *tmp = trim_str(tab[0]);
		char *tmp2 = trim_str(tab[1]);
		str = ft_strjoin(tmp, tmp2);
		return (str);
	}
}

char	*trim_parse(char *str)
{
    char	*dest;
    int		ret;
	int		xet;
	
	dest = trim_quote(str, &ret, &xet);
	if (ret % 2 != 0 && ret != 0)
	{
		printf("minishell > erreor quote parse \n");
		return (NULL);
	}
	else if (xet % 2 != 0 && xet != 0)
	{
		printf("minishell > erreor quote parse \n");
		return (NULL);
	}
	else
		return (trim_parse_ex(dest, str));
}

void		ft_non_built_funct(char *line)
{
	char		**arg;
	pid_t	pid = 0;
	int		stats = 0;
	int		pipe_fd[2];

	//arg = ft_strsplit(line, ' ');
	arg = split(line, "\n\t ");
	get_absolute_path(arg);

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(-1);
	}
	// On fork
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(-1);
	}
	// Si le fork a reussit, le processus pere attend l'enfant (process fork)
	else if (pid == 0)
    {
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], 1) == -1)
			perror("dup2");
      	else if (execve(arg[0], arg, NULL) == -1)
      		perror("execve");
    }
	else
    {
		char      buffer[2048];
		int       ret;
		int       status;

    	close(pipe_fd[1]);

		while ((ret = read(pipe_fd[0], buffer, 2048)) != 0)
		{
			printf("%d\n", ret);
			buffer[ret] = 0;
			printf("%s\n", buffer);
		}
		waitpid(pid, &stats, 0);
		set_env_var("?", ft_itoa(WEXITSTATUS(stats)));
		kill(pid, SIGTERM);
    }
}

void		parse_line_ext(char **str, char *line)
{
	if (strcmp(str[0], "echo") == 0 || strcmp(str[0], "/bin/echo") == 0)
		handle_echo(str[1]);
	else if (strcmp(str[0], "exit") == 0 || strcmp(str[0], "/bin/exit") == 0)
		exit_shell();
	else if (strcmp(str[0], "cd") == 0 || strcmp(str[0], "/bin/cd") == 0)
		handle_cd(str[1]);
	else if (strcmp(str[0], "env") == 0 || strcmp(str[0], "/bin/env") == 0)
		handle_env(str[0]);
	else if (strcmp(str[0], "pwd") == 0 || strcmp(str[0], "/bin/pwd") == 0)
		handle_pwd(str[1]);
	else
		ft_non_built_funct(line);
}

void		parse_line(char *line)
{
	char	**str;
	
	while (*line == ' ')
		line++;
	str = split_commande(line);
	if (strcmp(line, "") == 0)
		;
	else if (strcmp(line, "clear") == 0)
		system("clear");
	else if (line[0] == '"' || line[0] == '\'')
		trim_parse(line);
	else if (line[0] == '$')
	{
		ft_putstr(parse_dollar(line));
		strcmp(parse_dollar(line), " ") != 0 ? ft_putstr(": commande not valid \n") :  ft_putstr("\n");
	}
	else
		parse_line_ext(str, line);
	
}
