/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:18:47 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/14 18:57:21 by achahdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec(t_cmd *cmd)
{
	char *cmnd;

	cmnd = cmd->cmd;

	if (ft_strcmp("cd",cmnd) == 0)
		cd(cmd);
	if (ft_strcmp("export",cmnd) == 0)
		export(g_data.env_lst, cmd->args + 1);
	if (ft_strcmp("unset",cmnd) == 0)
		unset(cmd);
	if (ft_strcmp("echo",cmnd) == 0)
		echo(cmd);
	if (ft_strcmp("pwd",cmnd) == 0)
		pwd();
    if (ft_strcmp("env",cmnd) == 0)
		env();
	if (ft_strcmp("exit",cmnd) == 0)
		ft_exit(cmd);
}

void test_cmds()
{
	t_cmd *cmd;

	cmd = g_data.cmds;
	while (cmd)
	{
		exec(cmd);
		cmd = cmd->next;
	}
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
			test_cmds();
		free(line);
		clear_cmds_lst(g_data.cmds);
		line = readline(PROMPT);
	}
	return (0);
}
