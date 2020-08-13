
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

int				check_output(t_rdir *output_file)
{
	char	*old_file;

	while (output_file)
	{
		old_file = output_file->file_io;
		output_file->file_io = parse_quote(output_file->file_io, -1);
		free(old_file);
		if (output_file->over_write)
			output_file->fd = open(output_file->file_io, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
		else
			output_file->fd = open(output_file->file_io, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
		if (output_file->fd < 0)
			return (0);
		if (output_file->next)
			close(output_file->fd);
		output_file = output_file->next;
	}
	return (1);
}

int				check_input(t_rdir *input_file)
{
	char	*old_file;

	while (input_file)
	{
		old_file = input_file->file_io;
		input_file->file_io = parse_quote(input_file->file_io, -1);
		free(old_file);
		if ((input_file->fd = open(input_file->file_io, O_RDONLY)) < 0)
			return (no_file_error(NULL, input_file->file_io, 0));
		if (input_file->next)
			close(input_file->fd);
		input_file = input_file->next;
	}
	return (1);
}

void			set_redirect_dup2(t_cmd *cmd)
{
	t_rdir *last;

	if (cmd->input)
	{
		last = last_rdir(cmd->input);
		last->file_dup2 = dup(0);
		dup2(last->fd, 0);
	}
	if (cmd->output)
	{
		last = last_rdir(cmd->output);
		last->file_dup2 = dup(1);
		dup2(last->fd, 1);
	}
}

void			close_redirect_dup2(t_cmd *cmd)
{
	t_rdir	*last;

	if (cmd->input)
	{
		last = last_rdir(cmd->input);
		dup2(last->file_dup2, 0);
		close(last->file_dup2);
	}
	if (cmd->output)
	{
		last = last_rdir(cmd->output);
		dup2(last->file_dup2, 1);
		close(last->file_dup2);
	}
}
