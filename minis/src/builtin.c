/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarab <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 19:31:22 by yarab             #+#    #+#             */
/*   Updated: 2020/02/28 19:31:25 by yarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

en_builtin		builtinswitch(char *word)
{
	if (word == NULL)
		return (BI_NONE);
	else if (strlen(word) == 0)
		return (BI_NONE);
	else if (strcmp(word, "echo") == 0 || strcmp(word, "/bin/echo") == 0)
		return (BI_ECHO);
	else if (strcmp(word, "cd") == 0 || strcmp(word, "/bin/cd") == 0)
		return (BI_CHDIR);
	else if (strcmp(word, "pwd") == 0 || strcmp(word, "/bin/pwd") == 0)
		return (BI_PWD);
	else if (strcmp(word, "env") == 0 || strcmp(word, "/bin/env") == 0)
		return (BI_ENV);
	else if (strcmp(word, "setenv") == 0 || strcmp(word, "/bin/setenv") == 0)
		return (BI_SETENV);
	else if (strcmp(word, "unset") == 0 || strcmp(word, "/bin/unset") == 0)
		return (BI_UNSET);
	else if (strcmp(word, "exit") == 0 || strcmp(word, "quit") == 0 ||
		strcmp(word, "exit()") == 0 || strcmp(word, "quit()") == 0)
		return (BI_EXIT);
	else
		return (BI_NONE);
}

en_status		processbuiltincmd(char **words, int *fds)
{
	en_builtin			mode;

	mode = builtinswitch(words[0]);
	if (mode == BI_CHDIR && isPipe == 0)
		return (bultinCD(words));
	else if (mode == BI_PWD && isPipe == 0)
		return (bultinPWD(words));
	else if (mode == BI_ENV && isPipe == 0)
		return (bultinENV(words));
	else if (mode == BI_ECHO && isPipe == 0)
		return (bultinECHO(words));
	else if (mode == BI_SETENV && isPipe == 0)
		return (bultinSETENV(words));
	else if (mode == BI_UNSET && isPipe == 0)
		return (bultinUNSET(words));
	else if (mode == BI_EXIT)
		return (STATUS_EXIT);
	else if (mode == BI_NONE)
		return (STATUS_UNRECOGNIZED);
	else
		return (STATUS_UNRECOGNIZED);
}
