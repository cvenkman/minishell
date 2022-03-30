/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:49:18 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 21:49:18 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_fd_if_redirect(int redirect_fds[2])
{
	if (redirect_fds[0] > 0)
		if (dup2(redirect_fds[0], 0) == -1)
			perror_exit_bash("dup2");
	if (redirect_fds[1] != -1)
		if (dup2(redirect_fds[1], 1) == -1)
			perror_exit_bash("dup2");
}

/**
**	@brief		run script
**	@return		int	-1 if ft_stjoin problem, -3 if no such script
*/
static int	run_script(char **cmd, char **env)
{
	char	*str_path;
	char	*str_command;

	if (cmd[0][0] == '/')
	{
		execve(cmd[0], cmd, env);
		perror_exit_bash(cmd[0]);
	}
	else
	{
		str_path = getenv("PWD=");
		str_path = ft_strjoin(str_path, "/");
		str_command = ft_strjoin(str_path, cmd[0]);
		if (!str_command || !str_path)
			exit(EXIT_FAILURE);
		execve(str_command, cmd, env);
		perror_exit_bash(cmd[0]);
	}
	return (errno);
}

/**
**	@brief			run script or file(command)
**	@return	int		-2 if no such cmd, -3 if no scipt, -1 if ft_strjoin problem 
*/
static int	script_or_file(char **cmd, char **env, t_minish *minish)
{
	change_fd_if_redirect(((t_cmd *)minish->cmdlst->content)->rd_fds);
	if ((ft_strchr(cmd[0], '.') != 0 && ft_strchr(cmd[0], '/') != 0)
		|| ft_strchr(cmd[0], '/') != 0)
		return (run_script(cmd, env));
	else
		return (run_cmd(cmd, env));
}

/**
**	@brief			create fork and run command
**	@param	cmd		pointer to command with parameters
**	@return	int		-2 if no such cmd, -3 if no scipt, -1 if fork problem
*/
int	ft_command(char **cmd, char **env, t_minish *minish)
{
	pid_t	pid;
	int		ret;

	ret = 0;
	if (((t_cmd *)minish->cmdlst->content)->rd_fds[0] == -5)
		return (1);
	signal_pipes_cmd();
	pid = fork();
	if (pid < 0)
		return (perror_return_number("fork", errno));
	else if (pid == 0)
		ret = script_or_file(cmd, env, minish);
	if (pid > 0)
		waitpid(pid, &g_status, 0);
	if (g_status == 2)
		g_status = 130;
	else
		g_status = WEXITSTATUS(g_status);
	return (ret);
}
