/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:10:01 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 21:39:34 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
**	@brief				pwd builtin
**	@param	cmd_splited	command
**	@return	int			1 if problem with getcwd, else 0
*/
int	ft_pwd(char **cmd_splited, t_minish *minish)
{
	char	*pwd;
	int		fd_error;

	fd_error = 2;
	if (((t_cmd *)minish->cmdlst->content)->rd_fds[1] != -1)
		fd_error = ((t_cmd *)minish->cmdlst->content)->rd_fds[1];
	pwd = ft_calloc(5000, 1);
	if (!pwd)
		return (1);
	if (arr_len(cmd_splited) > 1)
		return (error_builtin(cmd_splited[0], fd_error));
	if (getcwd(pwd, 5000) == NULL)
	{
		perror("pwd");
		free(pwd);
		return (1);
	}
	if (((t_cmd *)minish->cmdlst->content)->rd_fds[1] != -1)
		ft_putendl_fd(pwd, ((t_cmd *)minish->cmdlst->content)->rd_fds[1]);
	else
		ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}
