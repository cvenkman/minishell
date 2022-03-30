/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 19:29:09 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 21:42:09 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_valid_n(char *str, bool *flag)
{
	unsigned int	i;

	i = 1;
	while (str[i] == 'n')
		i++;
	if (i == ft_strlen(str))
	{
		*flag = 1;
		return (i);
	}
	return (0);
}

static void	ne_ochen(char **cmd_splited, int fd)
{
	int		i;
	bool	flag;

	i = 1;
	flag = 0;
	if (arr_len(cmd_splited) > 1)
		if (cmd_splited[1][0] == '-' && cmd_splited[1][1] == 'n')
			while (cmd_splited[i] && check_valid_n(cmd_splited[i], &flag))
				i++;
	while (cmd_splited[i])
	{
		ft_putstr_fd(cmd_splited[i], fd);
		i++;
		if (cmd_splited[i] != NULL)
			write (fd, " ", 1);
	}
	if (flag == 0)
		write (fd, "\n", 1);
}

/**
**	@brief		echo builtin
**	@return	int	1 if problem with malloc, else 0
*/
int	echo(char **cmd_splited, t_minish *minish)
{
	if (((t_cmd *)minish->cmdlst->content)->rd_fds[1] != -1)
		ne_ochen(cmd_splited, ((t_cmd *)minish->cmdlst->content)->rd_fds[1]);
	else
		ne_ochen(cmd_splited, 1);
	return (0);
}
