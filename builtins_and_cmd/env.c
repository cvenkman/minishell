/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:10:22 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 21:48:42 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
**	@brief		env builtin
**	@param		cmd_splited		command
**	@return	int	0
*/
int	ft_env(char **cmd_splited, char **env, t_minish *minish)
{
	int		i;
	int		fd_error;

	i = 0;
	fd_error = 2;
	if (((t_cmd *)minish->cmdlst->content)->rd_fds[1] != -1)
		fd_error = ((t_cmd *)minish->cmdlst->content)->rd_fds[1] != -1;
	if (arr_len(cmd_splited) > 1)
		return (error_builtin(cmd_splited[0], fd_error));
	while (env[i])
	{
		if (ft_strchr(env[i], '=') != NULL)
		{
			if (((t_cmd *)minish->cmdlst->content)->rd_fds[1] != -1)
				ft_putendl_fd(env[i],
					((t_cmd *)minish->cmdlst->content)->rd_fds[1]);
			else
				ft_putendl_fd(env[i], 1);
		}
		i++;
	}
	return (0);
}
