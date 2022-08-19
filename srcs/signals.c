/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:55:04 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/19 16:58:45 by achahdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sig_int_handler(int sig)
{
	if (g_data.loc == PROMPT)
	{
		g_data.exit_code = 1;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_data.exit_code = 1;
	}
	if (g_data.loc == EXEC)
	{
		ft_putstr_fd("^C\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g_data.exit_code = 128 + sig;
	}
}

// void	sig_quit_handler(int sig)
// {
// }
