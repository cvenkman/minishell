/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:04:49 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 22:07:58 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_quotes(char **str, int i, char **env)
{
	char	quot;
	char	*tmp;

	if ((*str)[i] != '\"' && (*str)[i] != '\'')
		return (i);
	if ((*str)[i] == (*str)[i + 1])
	{
		tmp = chrdup((*str)[i + 1], 2);
		set_free((void **)str, replace_substr(*str, tmp, "", i));
		free(tmp);
		return (i);
	}
	quot = (*str)[i++];
	while ((*str)[i] && (*str)[i] != quot)
	{
		if ((*str)[i] == '$' && quot == '\"')
		{
			i = read_env(str, i, env);
			continue ;
		}
		i++;
	}
	return (i);
}
