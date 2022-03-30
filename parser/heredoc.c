/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:58:57 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 22:16:22 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc(const char *stop_w, char **env, const int *fd)
{
	char	*buf;
	int		i;

	i = -1;
	close(fd[0]);
	while (1)
	{
		buf = readline("> ");
		if (!buf)
			exit(2);
		if (!ft_strcmp(buf, stop_w))
			break ;
		while (buf[++i])
		{
			if (buf[i] == '$')
				i = read_env(&buf, i, env);
		}
		write(fd[1], buf, ft_strlen(buf));
		write(fd[1], "\n", 1);
	}
	return (0);
}

void	printnl_exit(void)
{
	write(2, "\n", 1);
	g_status = 1;
	exit(1);
}

void	heredoc_signal(void)
{
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, (void *)printnl_exit);
	signal(SIGQUIT, SIG_DFL);
}

int	parse_heredoc(char *stop_w, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		heredoc_signal();
		heredoc(stop_w, env, fd);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
	close(fd[1]);
	status = WEXITSTATUS(status);
	if (status == 1)
	{
		g_status = 1;
		close(fd[0]);
		return (-2);
	}
	return (fd[0]);
}
