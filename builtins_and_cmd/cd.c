/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:49:26 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 21:49:26 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cwd(void)
{
	char	*buf;

	buf = chmllc(ft_calloc(1024, sizeof(char)));
	getcwd(buf, 1024);
	set_free((void **)&buf, chmllc(ft_strdup(buf)));
	return (buf);
}

int	update_pwd_oldpwd(char **env, char *key)
{
	char	*pwd;
	int		pwdi;

	pwdi = get_envi(env, key);
	pwd = get_cwd();
	key = chmllc(ft_strjoin(key, "="));
	set_free((void **)&pwd, chmllc(ft_strjoin(key, pwd)));
	free (key);
	if (pwdi == -1)
	{
		free(pwd);
		return (-1);
	}
	set_free((void **)(env + pwdi), pwd);
	return (0);
}

int	change_dir(char *path)
{
	int	status;

	status = chdir(path);
	if (status)
	{
		free(path);
		return (cmd_not_found("cd", path, ": No such file or directory"));
	}
	return (0);
}

char	*get_path(char **env, char **cmd_splited)
{
	int		index;

	if (arr_len(cmd_splited) == 1)
	{
		index = get_envi(env, "HOME");
		if (index == -1)
		{
			cmd_not_found("cd", "HOME not set", NULL);
			return (NULL);
		}
		return (chmllc(ft_strdup(env[index] + ft_strlen("HOME="))));
	}
	else if (!ft_strcmp(cmd_splited[1], "-"))
	{
		index = get_envi(env, "OLDPWD");
		if (index == -1)
		{
			cmd_not_found("cd", "OLDPWD not set", NULL);
			return (NULL);
		}
		else
			return (chmllc(ft_strdup(env[index] + ft_strlen("OLDPWD="))));
	}
	else
		return (chmllc(ft_strdup(cmd_splited[1])));
}

int	cd(char **cmd_splited, char **env)
{
	char	*path;

	path = get_path(env, cmd_splited);
	update_pwd_oldpwd(env, "OLDPWD");
	if (path && !change_dir(path))
	{
		free(path);
		update_pwd_oldpwd(env, "PWD");
		return (0);
	}
	return (1);
}
