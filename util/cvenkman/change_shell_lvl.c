/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_shell_lvl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:17:55 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 22:17:55 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_value_from_env(t_minish *minish, char *key)
{
	int		i;
	char	*str;
	int		j;
	int		n;

	i = -1;
	j = 0;
	while (minish->env[++i])
	{
		n = ft_env_key_len(minish->env[i]);
		if (!ft_strncmp(minish->env[i], key, ft_strlen(key)))
		{
			str = malloc(sizeof(char) * (ft_strlen(minish->env[i]) - n));
			n++;
			while (minish->env[i][n])
				str[j++] = minish->env[i][n++];
			str[j] = '\0';
			return (str);
		}
	}
	return (NULL);
}

void	change_shell_lvl(t_minish *minish)
{
	int		i;
	char	*str_lvl;
	char	*str;

	i = 0;
	str_lvl = get_value_from_env(minish, "SHLVL=");
	if (!str_lvl)
		return ;
	while (minish->env[i])
	{
		if (!ft_strncmp(minish->env[i], "SHLVL",
				ft_env_key_len(minish->env[i])))
		{
			str = ft_itoa(ft_atoi(str_lvl) + 1);
			free(str_lvl);
			free(minish->env[i]);
			minish->env[i] = ft_strjoin("SHLVL=", str);
			if (!minish->env[i])
				perror_exit_bash("malloc");
			free(str);
			break ;
		}
		i++;
	}
}
