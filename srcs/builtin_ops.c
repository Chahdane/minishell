/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:13:47 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/21 16:21:52 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtin(t_cmd *cmd)
{
	if (ft_strcmp("cd", cmd->cmd) == 0
		|| !ft_strcmp("CD", cmd->cmd))
		return (1);
	if (ft_strcmp("export", cmd->cmd) == 0)
		return (1);
	if (ft_strcmp("unset", cmd->cmd) == 0)
		return (1);
	if (ft_strcmp("echo", cmd->cmd) == 0
		|| !ft_strcmp("ECHO", cmd->cmd))
		return (1);
	if (ft_strcmp("pwd", cmd->cmd) == 0
		|| !ft_strcmp("PWD", cmd->cmd))
		return (1);
	if (ft_strcmp("env", cmd->cmd) == 0
		|| !ft_strcmp("ENV", cmd->cmd))
		return (1);
	if (ft_strcmp("exit", cmd->cmd) == 0)
		return (1);
	return (0);
}

void	exec_builtin(t_cmd *cmd)
{
	if (ft_strcmp("cd", cmd->cmd) == 0
		|| !ft_strcmp("CD", cmd->cmd))
		cd(cmd);
	if (ft_strcmp("export", cmd->cmd) == 0)
		export(g_data.env_lst, cmd->args + 1);
	if (ft_strcmp("unset", cmd->cmd) == 0)
		unset(cmd);
	if (ft_strcmp("echo", cmd->cmd) == 0
		|| !ft_strcmp("ECHO", cmd->cmd))
		echo(cmd);
	if (ft_strcmp("pwd", cmd->cmd) == 0
		|| !ft_strcmp("PWD", cmd->cmd))
		pwd();
	if (ft_strcmp("env", cmd->cmd) == 0
		|| !ft_strcmp("ENV", cmd->cmd))
		env();
	if (ft_strcmp("exit", cmd->cmd) == 0)
		ft_exit(cmd);
}

int	run_one_builtin(void)
{
	int	stdout_fd;

	stdout_fd = dup(1);
	if (stdout_fd < 0)
	{
		ft_perror("minishell", NULL, 0);
		return (-1);
	}
	if (open_files(g_data.cmds))
		return (-1);
	if (g_data.cmds->out_file > -1)
		if (dup2(g_data.cmds->out_file, 1) < 0)
			return (-1);
	if (ft_strcmp("exit", g_data.cmds->cmd) == 0)
		ft_putendl_fd("exit", 2);
	exec_builtin(g_data.cmds);
	dup2(stdout_fd, 1);
	close(stdout_fd);
	return (0);
}
