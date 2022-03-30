/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:58:53 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 22:16:00 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_oflags(char redirect, bool is_double)
{
	int	oflags;

	if (redirect == '>')
	{
		oflags = O_CREAT | O_WRONLY;
		if (is_double)
			oflags |= O_APPEND;
		else
			oflags |= O_TRUNC;
	}
	else
		oflags = O_RDONLY;
	return (oflags);
}

int	change_line(char *const *line, int i, char **buf, int len)
{
	set_free((void **)buf, chmllc(ft_substr(*line, i, len)));
	set_free((void **)line, replace_substr(*line, (*buf), "", i));
	set_free((void **)line, shrink_chs_one(*line, i - 1, ' '));
	if (!(*line)[i + 1] && (*line)[i - 1])
		i--;
	set_free((void **)line, chmllc(ft_strtrim(*line, " \t")));
	free((*buf));
	return (i);
}

int	get_fd(char redirect, bool is_double, char *buf, char **env)
{
	int	res;

	if (redirect == '<' && is_double)
	{
		res = parse_heredoc(buf, env);
		if (res == -2)
			return (-2);
	}
	else
	{
		res = open(buf, get_oflags(redirect, is_double), 0644);
		if (res == -1)
		{
			if (errno == ENOTDIR)
				cmd_not_found(buf, "No such file or directory", NULL);
			else
				return (cmd_not_found(buf, strerror(errno), NULL));
		}
	}
	return (res);
}

void	init_fields(char *const *line, int i, bool *is_double, int *fname_start)
{
	(*is_double) = false;
	if ((*line)[i] == (*line)[i + 1])
		(*is_double) = true;
	(*fname_start) = i + (*is_double) + 1;
	if ((*line)[i + 1] == ' ' || ((*is_double) && (*line)[i + 1]
								  && (*line)[i + 2] == ' '))
		(*fname_start)++;
}

int	parse_redirect(char **line, int i, t_cmd *cmd, char **env)
{
	bool	is_double;
	int		index;
	char	*buf;
	int		fname_start;
	size_t	len;

	init_fields(line, i, &is_double, &fname_start);
	if ((*line)[fname_start] == '"' || (*line)[fname_start] == '\'')
	{
		buf = substr_till_chr(*line, (*line)[fname_start], fname_start + 1);
		chmllc(buf);
		len = ft_strlen(buf) + 2;
	}
	else
		len = parse_file_name(line, fname_start, &buf);
	index = 0;
	if ((*line)[i] == '>')
		index = 1;
	if (cmd->rd_fds[index] >= 0)
		close(cmd->rd_fds[index]);
	cmd->rd_fds[index] = get_fd((*line)[i], is_double, buf, env);
	return (change_line(line, i, &buf, len + fname_start - i));
}
