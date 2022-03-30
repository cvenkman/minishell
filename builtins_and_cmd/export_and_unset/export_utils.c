/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:21:52 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 21:44:28 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
**	@brief	write cmd: str: "not a valid identifier" in 2 fd
*/
void	not_valid_export(char *cmd, char *str)
{
	write(2, "bash: ", 6);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, "`", 1);
	write(2, str, ft_strlen(str));
	write(2, "'", 1);
	write(2, ": ", 2);
	write(2, "not a valid identifier\n", 24);
}

/**
**	@brief	return env key length (until =)
*/
int	ft_env_key_len(char *env)
{
	int	i;
	int	env_key_len;

	i = 0;
	env_key_len = 0;
	while (env[env_key_len] != '\0' && env[env_key_len] != '=')
		env_key_len++;
	return (env_key_len);
}

/**
**	@brief	return NULL and assign 1 to ret
*/
void	*return_flag(int *ret)
{
	*ret = 1;
	return (NULL);
}

/**
**	@brief	just copy str to export[i] and i++
**	@return	int	0 if malloc problem, else 1
*/
int	copy_str_for_norminette(char *str, char **export, int *i)
{
	export[*i] = ft_strdup(str);
	if (!export[(*i)++])
		return (0);
	return (1);
}
