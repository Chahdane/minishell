/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:18:47 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/13 02:57:28 by achahdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec(char **envp)
{
	char *cmd;

	cmd = g_data.cmds->cmd;
	if (ft_strcmp("cd",cmd) == 0)
		cd(envp);
	if (ft_strcmp("export",cmd) == 0)
		export(g_data.env_lst,g_data.cmds->args);
	if (ft_strcmp("unset",cmd) == 0)
		unset();
	if (ft_strcmp("echo",cmd) == 0)
		echo();
	if (ft_strcmp("pwd",cmd) == 0)
		pwd();
    if (ft_strcmp("env",cmd) == 0)
		env();
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
		/* if !parse_line, execute*/
		if (!parse_line(line))
			exec(envp);
		free(line);
		clear_cmds_lst(g_data.cmds);
		line = readline(PROMPT);
	}
	return (0);
}
