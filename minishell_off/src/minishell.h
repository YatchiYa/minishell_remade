
#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
#include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <dirent.h>
# include <stddef.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
#include <stdbool.h>    // bool
//#include <time.h>
#include <assert.h>     // assert()

# include "gnl/get_next_line.h"

# define IS_QUOTE(x) (x == '"' || x == '\'')


typedef enum {  BI_NONE, BI_CHDIR, BI_EXIT,
                BI_PWD, BI_ENV, BI_ECHO,
                BU_DOLLARS, BI_SETENV,
                BI_UNSET }
                                en_builtin;

typedef enum {  STATUS_SUCCESS=0, STATUS_FAILURE,
                STATUS_SOFT_FAILURE, // "Soft" failure
                STATUS_EXIT, STATUS_UNRECOGNIZED, STATUS_NULL }   en_status;


static const int MAX_PATH_SIZE = 1024;
static const int MAX_INPUT_SIZE = 255;

char	        		**g_envv;
int                     isPipe;
int                     ctrld;


en_status				pipeCmds(char* buffer);
en_status			    processCmd(char* buffer, char* envp[], int* fds);
en_status				processExternalCmd(char** argv, int num, char* envp[], int* fds);
int						strReplace(char* str, char match, char replace);
void					**freeArray(void ** pointerArray);
char					**strcpyArray(char** strings);
int						wordCount(char** words);
int						indexOf(char* str, const char* chars);
void					printStrings(char** strs);
char					**splitString(char* buffer, const char* sep, const char* substrsyms);
en_status               processBuiltinCmd(char** words, int* fds);
en_status				builtinChangeDir(char** words);
en_builtin				builtinSwitch(char* word);
int 			        handle_cd(char *path);
char		            *trim_parse(char *str);
en_status               bultinCD(char   **words);
void	                get_absolute_path(char **cmd);
en_status               bultinPWD(char   **words);
int                     handle_pwd(char *str);
en_status               bultinENV(char   **words);
int                     handle_env(char *cmd);
char                    *trim_queue(char *str);
int 			        handle_redirect_pwd(char *str);
int 			        handle_redirect_env(char *str);
void			        handle_redirect(char *str);
void			        handle_1(char *str, char c);
en_status               bultinECHO(char   **words);
void			        handle_2(char *str, char c);
int     		        handle_echo(char *str);
int 	                handle_redirect_echo(char *str);
en_status               bultinSETENV(char   **words);
int                     handle_export(char *str);
int		                handle_redirect_setenv(char *str);
en_status               bultinUNSET(char   **words);
int 			        handle_unset(char *str);
void	        	    *ft_memalloc(size_t size);
char			        *ft_itoa(int n);
char			        **ft_strsplit(char const *s, char c);
void	        	    ft_freestrarr(char **arr);
void	        	    exit_shell(void);
void	        	    ft_putstr(char *str);
void			        init_envv(int ac, char **av, char **envv);
void					init_arg(char **av);
void	        		ft_bzero(void *s, size_t n);
void        			signal_handler(int signo);
void        			signal_handler3(int signo);
void					signal_handler2(int signo);
void	        		display_prompt_msg(void);
void	        		set_env_var(char *key, char *value);
char	        		**realloc_envv(int new_size);
int		        		find_env_var(char *var);
char        			*get_env_var(char *var);
void					print_env(void);
int		        		envv_len(char **envv);
char					*trim_quote(char *str, int *ret, int *xet);
char					*delim_ptr(char *str);
int						search_delim(char *str, char c, int n);
int						ssx(char *str, char *delim);
int						ss(char c, char *delim);
char					**split_commande(char *line);
void    				remove_env_var(int var_pos);
char            		*malloc_sortie(int len);
int		        		calc_c(char *str, char c);
int		        		only_point(char *str);
char	        		*ft_strjoinch(char const *s1, char c);
int		        		ft_strstartswith(char *s1, char *s2);
char					*ft_strchr(const char *s, int c);
char            		**ft_split(char *str, char *charset);
char		  	  		*parse_dollar(char *str);

#endif // !MINISHELL_H
