
#include "minishell.h"

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	x;

	i = 0;
	j = 0;
	x = 0;
	while (dst[i] != 0)
		i++;
	while (src && src[j] != 0)
		j++;
	if (i < dstsize)
		j = i + j;
	else
		j = j + dstsize;
	while (src && src[x] != '\0' && i + 1 < dstsize)
		dst[i++] = src[x++];
	dst[i] = '\0';
	return (j);
}

int				check_output(t_rdir *out)
{
	char	*old_file;

	while (out)
	{
		old_file = out->file;
		out->file = parse_quote(out->file, -1);
		free(old_file);
		if (out->is_dbl)
			out->fd = open(out->file, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
		else
			out->fd = open(out->file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
		if (out->fd < 0)
			return (0);
		if (out->next)
			close(out->fd);
		out = out->next;
	}
	return (1);
}

int				check_input(t_rdir *in)
{
	char	*old_file;

	while (in)
	{
		old_file = in->file;
		in->file = parse_quote(in->file, -1);
		free(old_file);
		if ((in->fd = open(in->file, O_RDONLY)) < 0)
			return (no_file_error(NULL, in->file, 0));
		if (in->next)
			close(in->fd);
		in = in->next;
	}
	return (1);
}

void			set_redirect_dup2(t_cmd *cmd)
{
	t_rdir *last;

	if (cmd->in)
	{
		last = lst_last_rdir(cmd->in);
		last->std = dup(0);
		dup2(last->fd, 0);
	}
	if (cmd->out)
	{
		last = lst_last_rdir(cmd->out);
		last->std = dup(1);
		dup2(last->fd, 1);
	}
}

void			close_redirect_dup2(t_cmd *cmd)
{
	t_rdir	*last;

	if (cmd->in)
	{
		last = lst_last_rdir(cmd->in);
		dup2(last->std, 0);
		close(last->std);
	}
	if (cmd->out)
	{
		last = lst_last_rdir(cmd->out);
		dup2(last->std, 1);
		close(last->std);
	}
}
