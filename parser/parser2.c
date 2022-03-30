/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:04:59 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 22:09:15 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_control_chr(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

int	cmdlst_add_elm(t_minish *msh, const char *prev_pipe, int i)
{
	t_list	*lst_new;
	char	*cmd;

	cmd = chmllc(ft_substr(prev_pipe, 0, msh->line + i - prev_pipe));
	lst_new = create_node(cmd, NULL);
	ft_lstadd_back(&msh->cmdlst, lst_new);
	return (0);
}

void	divide_by_pipe(t_minish *msh)
{
	char	*prev_pipe;
	int		i;

	i = 0;
	prev_pipe = ft_strchr(msh->line, '|');
	if (prev_pipe)
	{
		prev_pipe = msh->line;
		while (msh->line[i])
		{
			if (msh->line[i] == '\'' || msh->line[i] == '"')
				i = skip_untill_chr(msh->line + i + 1,
						msh->line[i]) - msh->line;
			if (msh->line[i] == '|')
			{
				cmdlst_add_elm(msh, prev_pipe, i);
				prev_pipe = msh->line + i + 1;
			}
			i++;
		}
		if ((i > 0 && msh->line[i - 1] != '|') || prev_pipe == msh->line)
			cmdlst_add_elm(msh, prev_pipe, i);
	}
	else
		cmdlst_add_elm(msh, msh->line, ft_strlen(msh->line));
}

int	if_quots_or_space(char **cmd, char ***cmd_splited, int *i, int *prev_spc)
{
	if ((*cmd)[(*i)] == '\"' || (*cmd)[(*i)] == '\'')
	{
		set_free((void **) cmd,
			replace_substr((*cmd), chstr((*cmd)[(*i)]), "", (*i)));
		(*i) = skip_untill_chr((*cmd) + (*i), chstr(-1)[0]) - (*cmd);
		set_free((void **) cmd, replace_substr((*cmd), chstr(-1), "", (*i)));
		return (1);
	}
	if ((*cmd)[(*i)] == ' ')
	{
		(*cmd_splited) = strarr_add((*cmd_splited),
				arr_len((*cmd_splited)), chmllc(ft_substr((*cmd),
						(*prev_spc), (*i) - (*prev_spc))));
		(*prev_spc) = (*i) + 1;
	}
	return (0);
}

char	**get_cmd_splited(char *line, t_cmd *cmd,
			char **env, char **cmd_splited)
{
	int	i;
	int	prev_spc;

	i = 0;
	line = ft_strdup(line);
	prev_spc = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			i = parse_redirect(&line, i, cmd, env);
			if (i == -2)
				return (NULL);
			continue ;
		}
		if (if_quots_or_space(&line, &cmd_splited, &i, &prev_spc))
			continue ;
		i++;
	}
	if (prev_spc < i)
		cmd_splited = strarr_add(cmd_splited, arr_len(cmd_splited),
				chmllc(ft_substr(line, prev_spc, i - prev_spc)));
	free(line);
	return (cmd_splited);
}
