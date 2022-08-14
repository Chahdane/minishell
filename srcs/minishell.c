/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:18:47 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/14 01:07:38 by achahdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec(void)
{
	char *cmd;

	cmd = g_data.cmds->args[0];
	if (ft_strcmp("cd",cmd) == 0)
		cd();
	if (ft_strcmp("export",cmd) == 0)
		export(g_data.env_lst, (g_data.cmds->args) + 1);
	if (ft_strcmp("unset",cmd) == 0)
		unset();
	if (ft_strcmp("echo",cmd) == 0)
		echo();
	if (ft_strcmp("pwd",cmd) == 0)
		pwd();
    if (ft_strcmp("env",cmd) == 0)
		env();
	if (ft_strcmp("exit",cmd) == 0)
		ft_exit();
}


int	main(int ac, char **av, char **envp)
{
	char	*line;

	(void) ac;
	(void) av;

	init_env_lst(envp);
	line = readline(PROMPT);
	while (line)
	{
		ft_add_history(line);
		if (!parse_line(line) && g_data.cmds)
			exec();
		free(line);
		clear_cmds_lst(g_data.cmds);
		line = readline(PROMPT);
	}
	return (0);
}
