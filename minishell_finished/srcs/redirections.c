
#include "minishell.h"

t_rdir		*new_rdir(char *file, int mode)
{
	t_rdir *new;

	new = malloc(sizeof(t_rdir));
	new->file_io = ft_strdup(file);
	new->file_dup2 = -1;
	new->over_write = mode;
	new->next = NULL;
	return (new);
}

t_rdir		*last_rdir(t_rdir *begin)
{
	while (begin->next)
		begin = begin->next;
	return (begin);
}

t_rdir		*add_rdir(t_rdir *begin, char *file, int mode)
{
	t_rdir *last;

	if (!begin)
		return (new_rdir(file, mode));
	last = last_rdir(begin);
	last->next = new_rdir(file, mode);
	return (begin);
}

void		add_redir_cmd(t_cmd *cmd, char *redir, char *file)
{
	t_cmd *last;

	last = last_cmd(cmd);
	last->is_rdir = 1;
	if (trim_queue(redir, "<"))
		last->input = add_rdir(last->input, file, 0);
	else if (trim_queue(redir, ">"))
		last->output = add_rdir(last->output, file, 0);
	else if (trim_queue(redir, ">>"))
		last->output = add_rdir(last->output, file, 1);
}
