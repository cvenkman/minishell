/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:18:52 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 21:46:59 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
**	@brief	wait all cahild processes in parent process
*/
static void	wait_all_process(t_list	*head)
{
	while (head)
	{
		if (head->next)
			waitpid(((t_cmd *)head->content)->pid, NULL, 0);
		else
		{
			waitpid(((t_cmd *)head->content)->pid, &g_status, 0);
			if (g_status == 2)
				g_status = 130;
			else
				g_status = WEXITSTATUS(g_status);
		}
		head = head->next;
	}
}

/**
**	@brief	close all fd if it's not a 0/1/2
*/
void	close_pipes(t_list	*elem)
{
	while (elem)
	{
		if (((t_cmd *)elem->content)->fd_in > 2)
			close(((t_cmd *)elem->content)->fd_in);
		if (((t_cmd *)elem->content)->fd_out > 2)
			close(((t_cmd *)elem->content)->fd_out);
		elem = elem->next;
	}
}

/**
**	@brief					create fork & executes the command or builtin & close pipes
**	@param	elem			struct with command
**	@param	next_fd_in		fd_in for next command
*/
static int	process(char **env, t_list *elem, int next_fd_in, t_minish *minish)
{
	next_fd_in = 0;
	((t_cmd *)elem->content)->pid = fork();
	if (((t_cmd *)elem->content)->pid < 0)
		return (0);
	if (((t_cmd *)elem->content)->pid == 0)
	{
		if (next_fd_in > 2)
			close(next_fd_in);
		if (dup2(((t_cmd *)elem->content)->fd_out, STDOUT_FILENO) == -1)
			perror_exit("dup2");
		if (distribution(minish, ((t_cmd *)elem->content)->cmd_splited, true))
			exit (0);
		if (dup2(((t_cmd *)elem->content)->fd_in, STDIN_FILENO) == -1)
			perror_exit("dup2");
		close_pipes(elem);
		run_cmd(((t_cmd *)elem->content)->cmd_splited, env);
	}
	return (1);
}

/**
**	@brief		create pipes for all commands
*/
static int	do_pipes(t_list *elem, char **env, t_minish *minish)
{
	int	fd[2];

	while (elem)
	{
		if (((t_cmd *)elem->content)->rd_fds[0] == -5)
			elem = elem->next;
		fd[0] = STDIN_FILENO;
		fd[1] = STDOUT_FILENO;
		if (elem->next)
			pipe(fd);
		if (((t_cmd *)elem->content)->rd_fds[0] > 0)
			fd[0] = ((t_cmd *)elem->content)->rd_fds[0];
		if (((t_cmd *)elem->content)->rd_fds[1] > 0)
			fd[1] = ((t_cmd *)elem->content)->rd_fds[1];
		((t_cmd *)elem->content)->fd_out = fd[1];
		if (elem->next)
			((t_cmd *)elem->next->content)->fd_in = fd[0];
		if (!process(env, elem, fd[0], minish))
			return (0);
		if (((t_cmd *) elem->content)->fd_out > 2)
			close(((t_cmd *)elem->content)->fd_out);
		elem = elem->next;
	}
	return (1);
}

/**
**	@brief		run commands and builtins with pipes
*/
void	ft_pipes(t_minish *minish, char **env)
{
	t_list	*elem;
	t_list	*head;

	signal_pipes_cmd();
	if (((t_cmd *)minish->cmdlst->content)->rd_fds[0] == -5)
		minish->cmdlst = minish->cmdlst->next;
	elem = minish->cmdlst;
	head = elem;
	((t_cmd *)elem->content)->fd_out = STDOUT_FILENO;
	((t_cmd *)elem->content)->fd_in = STDIN_FILENO;
	if (((t_cmd *)elem->content)->rd_fds[0] > 0)
		((t_cmd *)elem->content)->fd_in = ((t_cmd *)elem->content)->rd_fds[0];
	if (((t_cmd *)elem->content)->rd_fds[1] > 0)
		((t_cmd *)elem->content)->fd_out = ((t_cmd *)elem->content)->rd_fds[1];
	if (!do_pipes(elem, env, minish))
		perror_return("fork");
	elem = head;
	close_pipes(elem);
	wait_all_process(head);
}
