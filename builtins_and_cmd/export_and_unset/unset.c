/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:44:46 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 21:43:51 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_valid_unset(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	valid_unset_len(char **cmd_splited, char **env)
{
	int	i;
	int	k;
	int	env_key_len;
	int	len;

	k = 1;
	len = 0;
	while (cmd_splited[k])
	{
		i = 0;
		while (env[i])
		{
			env_key_len = ft_env_key_len(env[i]);
			if (env_key_len == (int)ft_strlen(cmd_splited[k]))
				if (!ft_strncmp(env[i], cmd_splited[k], env_key_len))
					len++;
			i++;
		}
		k++;
	}
	return (len);
}

/**
**	@brief		check if necessary remove(unset) this env_str
**	@return	int	1 if yes, 0 if no
*/
static int	minishell_ebanyi(char **cmd_splited, char *env)
{
	int	k;
	int	env_key_len;

	k = 1;
	env_key_len = ft_env_key_len(env);
	while (cmd_splited[k])
	{
		if (env_key_len == (int)ft_strlen(cmd_splited[k]))
		{
			if (!ft_strncmp(env, cmd_splited[k], env_key_len))
				return (1);
		}
		k++;
	}
	return (0);
}

static char	**remove_from_export(char **cmd_splited, char **env, char **new_env)
{
	int	i;
	int	env_key_len;
	int	j;

	i = 0;
	j = 0;
	env_key_len = 0;
	while (env[i])
	{
		env_key_len = ft_env_key_len(env[i]);
		if (minishell_ebanyi(cmd_splited, env[i]))
		{
			i++;
			continue ;
		}
		new_env[j] = ft_strdup(env[i]);
		i++;
		j++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int	unset(char **cmd_splited, char **env, t_minish *minish)
{
	int		len;
	int		k;
	char	**new_env;

	k = 1;
	while (cmd_splited[k])
	{
		if (!check_valid_unset(cmd_splited[k]))
			not_valid_export("unset", cmd_splited[k]);
		k++;
	}
	len = valid_unset_len(cmd_splited, env);
	if (len == 0 || k == (arr_len(cmd_splited) - 1))
		return (1);
	new_env = ft_calloc(sizeof(char *), (arr_len(env) - len + 1));
	if (!new_env)
		return (1);
	minish->env = remove_from_export(cmd_splited, env, new_env);
	free_arr(env);
	return (0);
}
