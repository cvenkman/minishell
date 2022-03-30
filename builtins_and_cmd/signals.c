/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:46:35 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 21:57:49 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "../minishell.h"

void	ctrl_ign(void)
{
	struct termios	ts;

	tcgetattr(STDIN_FILENO, &ts);
	ts.c_lflag = ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &ts);
}

static void	handle_sigint(void)
{
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_status = 1;
}

void	main_signals(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, (void *)handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	change_global(void)
{
	write(2, "\n", 1);
	g_status = 130;
}

void	signal_pipes_cmd(void)
{
	signal(SIGINT, (void *)change_global);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}
