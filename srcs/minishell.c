/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:18:47 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/20 23:19:54 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **envp)
{
	char	*line;

	(void) ac;
	(void) av;
	init_env_lst(envp);
	g_data.loc = PROMPT;
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, sig_quit_handler);
	line = readline("MINISHELL$> ");
	while (line)
	{
		g_data.sig_caught = 0;
		ft_add_history(line);
		if (!parse_line(line) && g_data.cmds)
			ft_execute(g_data.cmds);
		free(line);
		clear_cmds_lst(g_data.cmds);
		g_data.loc = PROMPT;
		line = readline("MINISHELL$> ");
	}
	ft_putendl_fd("exit", 2);
	return (0);
}
