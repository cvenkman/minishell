/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:17:36 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 22:17:48 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*chmllc(void *ptr)
{
	if (ptr == NULL)
	{
		ft_putstr_fd("malloc error\n", 2);
		exit(MALLOC_ERROR);
	}
	return (ptr);
}

t_list	*create_node(char *cmd, char **cmd_splited)
{
	t_cmd	*elem;

	elem = chmllc(ft_calloc(1, sizeof(t_cmd)));
	elem->cmd = cmd;
	elem->cmd_splited = cmd_splited;
	elem->rd_fds[0] = -1;
	elem->rd_fds[1] = -1;
	return (chmllc(ft_lstnew(elem)));
}

void	destroy_node(void *content)
{
	t_cmd	*cast;
	int		i;
	int		len;

	i = 0;
	cast = (t_cmd *)content;
	set_free((void **)&cast->cmd, NULL);
	len = arr_len(cast->cmd_splited);
	while (i < len)
	{
		free(cast->cmd_splited[i]);
		i++;
	}
	set_free((void **)&cast->cmd_splited, NULL);
	free(cast);
}

/**
 * free <b><i>var</i></b> and set it <b><i>new</i></b>
 * @param var pointer to the variable with pointer that will be freed
 * @param new value that will be wrote to <b><i>var</i></b> after liberation
 */
void	set_free(void **var, void *new)
{
	void	*tmp;

	if (var == NULL)
		return ;
	if (*var == new)
		return ;
	tmp = *var;
	*var = new;
	if (tmp)
		free(tmp);
}
