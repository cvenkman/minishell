/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:29:07 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 22:29:07 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_status;

void	ctrl_d(void)
{
	write(2, "exit\n", 5);
	exit(g_status);
}

static void	ne_ochen(int argc, char **argv, char **env, t_minish *minish)
{
	(void)argc;
	(void)argv;
	rl_outstream = stderr;
	minish->cmdlst = NULL;
	minish->env = copystr_array(env);
	change_shell_lvl(minish);
	ctrl_ign();
}

int	main(int argc, char **argv, char **env)
{
	t_minish	m;

	ne_ochen(argc, argv, env, &m);
	while (1)
	{
		main_signals();
		m.line = readline("\x1b[32mminishell$>\x1b[0m ");
		if (m.line == NULL)
			ctrl_d();
		if (m.line[0])
			add_history(m.line);
		else
		{
			free(m.line);
			m.line = NULL;
			continue ;
		}
		if (!parser(&m) && m.line[0]
			&& ((t_cmd *)m.cmdlst->content)->cmd_splited)
			distribution(&m, ((t_cmd *) m.cmdlst->content)->cmd_splited, false);
		ft_lstclear(&m.cmdlst, &destroy_node);
		free(m.line);
		m.line = NULL;
	}
	return (0);
}
