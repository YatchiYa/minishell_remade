/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:13:46 by pray              #+#    #+#             */
/*   Updated: 2020/02/21 14:13:49 by pray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define WHITE_SPACE " tnvfr"
# define SEP_SPACE " \t<>|;"
# define SEP "<>|;"
# define SPACE " \t"
# define PATH_MAX 1024
# define LINE_MAX 100024
# define NO_EXCODE -1
# define NO_STATUS -1

# include "tools.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>

# define CMD_ECHO "echo"
# define CMD_EXIT "echo"
# define CMD_ENV "echo"
# define CMD_EXPORT "echo"
# define CMD_PWD "echo"
# define CMD_UNSET "echo"
# define CMD_UNSET "echo"

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_rdir
{
	char			*file_io;
	int				fd;
	int				over_write;
	int				file_dup2;
	struct s_rdir	*next;
}					t_rdir;

typedef struct		s_cmd
{
	char			**argv;
	int				is_pipe;
	int				is_rdir;
	int				has_path;
	int				start_dollars;
	t_rdir			*input;
	t_rdir			*output;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_minish
{
	t_env			*env;
	t_cmd			*cmd;
	char			*line;
	char			**argv;
	int				cmd_is_ok;
	int				signal_is_called;
	int				is_end_of_file;
	int				ret;
	int				quote_found;
	int				comment_found;
	int				output_first;
	int				input_first;
	int				free_or_not;
	int				exit_cmd;
}					t_minish;

t_minish			*get_minish(void);
void				init_env(char **env);
int					ft_getline(void);
void				display_prompt_msg(void);
int					ft_is_sep_space(const char *s, char c);
int					check_sep(char *line, int i, int use);
int					trim_quote(char *line, int i);
char				*check_quote(char *tk, int i);
int					check_errors_arg(char **argv);
int					word_str_count(char *line);
int					trim_space(char *line, int i, int jmp);
int					jmp_quotes(char *line, int i);
int					init_cmd(char **argv, int i, int ret);
int					check_errors_arg(char **argv);
int					is_point_virgule(char **argv);
int					is_pipe(char **argv);
int					is_redirections(char **argv);
int					is_redir_quote(char *s);
int					ft_strcmp_v2(const char *s1, const char *s2);
t_cmd				*add_cmd(t_cmd *begin, char *token);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s1);
t_cmd				*last_cmd(t_cmd *cmd);
t_cmd				*create_cmd(char *data);
void				free_1(void);
t_cmd				*pipe_cmd_call(t_cmd *cmd);
int					is_builtin(char *arg);
void				get_signal_builtin_cmd(int status, int signo);
int					handle_dollars_parse(t_cmd *cmd, int i);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					check_output(t_rdir *out);
int					check_dollar(t_cmd *cmd);
int					check_input(t_rdir *in);
char				*parse_quote(char *argv, int i);
void				set_redirect_dup2(t_cmd *cmd);
void				close_redirect_dup2(t_cmd *cmd);
int					exec_builtin(int btin_nb, t_cmd *cmd);
int					handle_echo(t_cmd *cmd);
int					handle_pwd(t_cmd *cmd);
int					handle_export(t_cmd *cmd);
void				add_data(char *key, char *value);
t_env				*new_data(char *key, char *value);
int					handle_unset(t_cmd *cmd);
int					handle_env(t_cmd *cmd);
int					handle_exit(t_cmd *cmd);
char				*find_env(char *key);
int					handle_cd(t_cmd *cmd);
void				free_env(void);
void				free_all(void);
void				free_line(void);
int					count_arg(char **argv);
void				exec_non_builtin(t_cmd *cmd);
char				**get_env_full(t_env *env);
void				free_env_2(char **env);
void				error_minishell(void);
int					error_commande(char *cmd, int ret);
int					syntax_error(char *token, int ret);
int					no_file_error(char *cmd, char *file, int ret);
int					too_many_arg_error(char *cmd, int ret);
void				exec_command(int ret);
void				eof_exit(void);
void				get_exit_code(int status, int excode);
int					file_too_long(char *cmd, char *file, int ret);
t_rdir				*last_rdir(t_rdir *begin);
void				add_redir_cmd(t_cmd *cmd, char *redir, char *file);
int					wordcount_arg(char **arr);
t_rdir				*add_rdir(t_rdir *begin, char *file, int mode);
int					nb_pipes(t_cmd *cmd_list);
int					check_digit(char **argv, int cnt);
void				split_dollar_parse(char buf_tmp[2][LINE_MAX], char *arg);
int					parse_home(char *argv, char *buff, int *j);
int					ret_ext(void);
void				free_argv(void);
char				*parse_quote_2(char *argv, int i);
int					backslash_parse(char *arg, char *buff, int *j, int quotes);
int					get_value_dollars_parse(char *arg, char *buff, int *j);
char				*parse_quote_3(char *argv, int i);
int					get_env_data(char key[], char *arg);
char				*ft_split_arguments_extends(char *line, int index,
						int start, int count);
char				*ft_split_arguments_extends(char *line, int index,
						int start, int count);
char				**ft_split_arguments(char *line);
char				**trim_argv_2(char **argv);
char				**trim_arg_cmd(char **argv);
void				print_cmd(void);
void				free_11(void);
void				free_redirections(t_cmd *cmd);
void				free_line(void);
void				execrrr(t_cmd *cmd, char **path_arr);
char				**tab_join(char **tab, char **argv);
char				*parse_quote_q(char *argv, int i, t_cmd *cmd);
int					is_builtin_ext(char *arg, int i);
void				ext_non_built(t_cmd *cmd, char **tmp);
int					trim_backslash_2(char *line, int *i);
int					trim_quote_2(char *line, int i);
int					trim_backslash(char *line, int *i, char quote);

#endif
