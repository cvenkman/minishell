/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 23:18:14 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 21:45:44 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	putstr_in_export(char *export, int fd)
{
	int	i;

	i = 0;
	while (export[i] != '=')
	{
		write(fd, &export[i], 1);
		i++;
	}
	write(fd, &export[i], 1);
	i++;
	write(fd, "\"", 1);
	while (export[i])
	{
		write(fd, &export[i], 1);
		i++;
	}
	write(fd, "\"", 1);
	write(fd, "\n", 1);
}

static void	nraitsa__ne_ochen(char **export, int fd)
{
	int	i;

	i = 0;
	while (export[i])
	{
		if (ft_strncmp(export[i], "_=", 2) != 0)
		{
			ft_putstr_fd("declare -x ", fd);
			if (ft_strchr(export[i], '='))
				putstr_in_export(export[i], fd);
			else
				ft_putendl_fd(export[i], fd);
		}
		i++;
	}
}

void	print_export(char **export, t_minish *minish)
{
	if (((t_cmd *)minish->cmdlst->content)->rd_fds[1] != -1)
		nraitsa__ne_ochen(export,
			((t_cmd *)minish->cmdlst->content)->rd_fds[1]);
	else
		nraitsa__ne_ochen(export, 1);
}
