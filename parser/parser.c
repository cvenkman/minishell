/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:58:45 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 22:10:38 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_tilda(char **cmd, char **env, int i)
{
	int		index;

	index = get_envi(env, "HOME");
	if (index == -1)
		set_free((void **) cmd, replace_substr((*cmd), "~", "", i));
	else
		set_free((void **) cmd, replace_substr((*cmd), "~",
				env[index] + ft_strlen("HOME="), i));
	return (*cmd);
}

char	*parse_line(char *cmd, char **env)
{
	int		i;

	i = 0;
	set_free((void **)&cmd, ft_strtrim(cmd, " \t"));
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			i = parse_quotes(&cmd, i, env);
		else if (cmd[i] == '$')
		{
			i = read_env(&cmd, i, env);
			if (cmd[i] == ' ')
				set_free((void **)&cmd, shrink_chs_one(cmd, i - 1, ' '));
			continue ;
		}
		else if (cmd[i] == '~' && cmd[i - 1] == ' '
			&& (cmd[i + 1] == '/' || cmd[i + 1] == ' ' || !cmd[i + 1]))
			cmd = replace_tilda(&cmd, env, i);
		i++;
	}
	return (cmd);
}

int	shrink_spaces(char *const *line, int i)
{
	if ((*line)[i] == '\'' || (*line)[i] == '"')
		i = skip_untill_chr(*line + i + 1, (*line)[i]) - *line;
	else if ((*line)[i] == '\t')
	{
		set_free((void **)line, replace_substr(*line, chstr('\t'), " ", i));
		set_free((void **)line, shrink_chs_one(*line, --i, ' '));
		return (i);
	}
	else if ((*line)[i] == ' ')
		set_free((void **)line, shrink_chs_one(*line, i, ' '));
	return (i);
}

int	preparser(char **l, bool flag)
{
	int	i;

	set_free((void **)l, chmllc(ft_strtrim(*l, " \t")));
	if (!(*l)[0])
		return (0);
	i = -1;
	while ((*l)[++i])
	{
		if (((*l)[i] == '>' || (*l)[i] == '<') && (*l)[i] == (*l)[i + 1])
			i++;
		if (is_control_chr((*l)[i]))
		{
			if (flag)
				return (print_sintaxerr((*l)[i]));
			else
				flag = true;
			continue ;
		}
		else if ((*l)[i] != ' ' && (*l)[i] != '\t')
			flag = false;
		i = shrink_spaces(l, i);
	}
	if (flag)
		return (print_sintaxerr((*l)[i]));
	return (0);
}

int	parser(t_minish *minish)
{
	t_list	*elem;
	t_cmd	*cast;

	signal_pipes_cmd();
	if (preparser(&minish->line, false))
		return (-1);
	divide_by_pipe(minish);
	elem = minish->cmdlst;
	while (elem)
	{
		cast = elem->content;
		cast->cmd = parse_line(cast->cmd, minish->env);
		cast->cmd_splited = get_cmd_splited(cast->cmd, cast, minish->env, NULL);
		if (!cast->cmd_splited)
			break ;
		elem = elem->next;
	}
	minish->line = parse_line(minish->line, minish->env);
	main_signals();
	return (0);
}
