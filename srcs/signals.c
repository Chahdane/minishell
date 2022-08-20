/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:55:04 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/20 23:37:41 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_redisplay(void)
{
	g_data.exit_code = 1;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_int_handler(int sig)
{

	if (g_data.loc == PROMPT)
		ft_redisplay();
	else if (g_data.loc == EXEC)
	{
		ft_putstr_fd("^C\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		if (!g_data.last_cmd_returned)
		{
			g_data.exit_code = 128 + sig;
			g_data.sig_caught = 1;
		}
	}
	else
	{
		g_data.sig_caught = 1;
		close(0);
		ft_redisplay();
	}
}

void	sig_quit_handler(int sig)
{
	(void) sig;
	rl_on_new_line();
	if (g_data.loc == PROMPT || g_data.loc == HDOC)
		rl_redisplay();
	else if (g_data.loc == EXEC)
	{
		if (!g_data.last_cmd_returned)
		{
			g_data.exit_code = sig + 128;
			g_data.sig_caught = 1;
		}
		printf("^\\");
		if (cmd_lst_len(g_data.cmds) == 1)
			printf("Quit: 3\n");
	}
}
