/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:13:47 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/15 00:45:04 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtin(t_cmd *cmd)
{
	if (ft_strcmp("cd", cmd->cmd) == 0)
		return (1);
	if (ft_strcmp("export", cmd->cmd) == 0)
		return (1);
	if (ft_strcmp("unset", cmd->cmd) == 0)
		return (1);
	if (ft_strcmp("echo", cmd->cmd) == 0)
		return (1);
	if (ft_strcmp("pwd", cmd->cmd) == 0)
		return (1);
	if (ft_strcmp("env", cmd->cmd) == 0)
		return (1);
	if (ft_strcmp("exit", cmd->cmd) == 0)
		return (1);
	return (0);
}

void	check_builtin(t_cmd *cmd)
{
	if (ft_strcmp("cd", cmd->cmd) == 0)
		cd(cmd);
	if (ft_strcmp("export", cmd->cmd) == 0)
		export(g_data.env_lst, cmd->args + 1);
	if (ft_strcmp("unset", cmd->cmd) == 0)
		unset(cmd);
	if (ft_strcmp("echo", cmd->cmd) == 0)
		echo(cmd);
	if (ft_strcmp("pwd", cmd->cmd) == 0)
		pwd();
	if (ft_strcmp("env", cmd->cmd) == 0)
		env();
	if (ft_strcmp("exit", cmd->cmd) == 0)
		ft_exit(cmd);
}

void	run_one_builtin(void)
{
	int	stdout_fd;

	stdout_fd = dup(1);
	if (stdout_fd < 0)
	{
		ft_perror("minishell", NULL, 0);
		return ;
	}
	if (open_files(g_data.cmds))
		return ;
	if (g_data.cmds->out_file > -1)
		if (dup2(g_data.cmds->out_file, 1) < 0)
			return ;
	if (ft_strcmp("exit", g_data.cmds->cmd) == 0)
		ft_putendl_fd("exit", 2);
	check_builtin(g_data.cmds);
	dup2(stdout_fd, 1);
	close(stdout_fd);
}
