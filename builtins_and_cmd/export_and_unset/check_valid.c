/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 01:59:43 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 21:44:14 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_same_key(char *str, char **env)
{
	int	i;
	int	key_len;
	int	env_key_len;

	i = 0;
	key_len = 0;
	while (str[key_len] != '\0' && str[key_len] != '=')
		key_len++;
	while (env[i])
	{
		if (!ft_strcmp(str, env[i]))
			return (2);
		env_key_len = ft_env_key_len(env[i]);
		if (env_key_len == key_len)
			if (!ft_strncmp(str, env[i], key_len))
				return (SAME_KEY);
		i++;
	}
	return (ALL_GOOD);
}

/**
**	@brief		check valid args
**	@return	int 2 if str start from _=, NOT_VALID, SAME_KEY or ALL_GOOD
*/
int	check_valid(char *str, int *ret, char **env)
{
	int	i;

	i = 0;
	if (str[0] == '=' || ft_isdigit(str[0]))
		return (NOT_VALID);
	if (!ft_strncmp(str, "_=", 2))
		return (2);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			if (ret != NULL)
				*ret = 1;
			return (NOT_VALID);
		}
		i++;
	}
	return (check_same_key(str, env));
}

/**
**	@return	int	return valid export length in cmd_splited
*/
int	valid_export_len(char **cmd_splited, char **env)
{
	int		i;
	int		valid_export;

	i = 1;
	valid_export = 0;
	while (cmd_splited[i])
	{
		if (check_valid(cmd_splited[i], NULL, env) == ALL_GOOD)
			valid_export++;
		i++;
	}
	return (valid_export);
}

/**
**	@brief		check all args for valid
**	@return	int	1 if all valid, 0 if not
*/
int	all_not_valid(char **cmd_splited, char **env)
{
	int	not_valid;
	int	i;

	i = 1;
	not_valid = 0;
	while (cmd_splited[i])
	{
		if (check_valid(cmd_splited[i], NULL, env) == NOT_VALID)
		{
			not_valid_export("export", cmd_splited[i]);
			not_valid++;
		}
		else if (check_valid(cmd_splited[i], NULL, env) == 2)
			not_valid++;
		i++;
	}
	if (not_valid != (arr_len(cmd_splited) - 1))
		return (1);
	return (0);
}
