/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 21:30:51 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/18 20:05:46 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_streams(t_cmd *cmd, int last_in, int pipes[2])
{
	close(pipes[0]);
	if (cmd->input_source == STDIN)
	{
		dup2(last_in, 0);
		if (last_in != 0)
			close(last_in);
	}
	else if (cmd->input_source == INFILE)
		dup2(cmd->in_file, 0);
	else
		dup2(cmd->heredoc, 0);
	if (cmd->out_file == -1)
	{
		if (cmd->next)
			dup2(pipes[1], 1);
	}
	else
		dup2(cmd->out_file, 1);
	close(pipes[1]);
	return (0);
}

void	forked_process(t_cmd *cmd, int last_in, int pipes[2])
{
	char	*path;

	handle_streams(cmd, last_in, pipes);
	if (!cmd->cmd)
		exit(0);
	if (is_builtin(cmd))
	{
		exec_builtin(cmd);
		exit(g_data.exit_code);
	}
	if (ft_strchr(cmd->cmd, '/'))
	{
		if (!access(cmd->cmd, F_OK) && cmd->cmd[ft_strlen(cmd->cmd) - 1] == '/')
			exit(ft_perror("minishell", ft_strjoin(cmd->cmd, ": is a directory"), 1) + 127);
		if (execve(cmd->cmd, cmd->args, g_data.env))
		{
			if (errno == 2)
				exit(ft_perror(ft_strjoin("minishell: ", cmd->cmd), NULL, 0) + 128);
			else
				exit(ft_perror(ft_strjoin("minishell: ", cmd->cmd), NULL, 0) + 127);
		}
	}
	else
	{
		path = check_path(cmd->cmd, g_data.env_lst);
		if (!path)
				exit(ft_perror("minishell", ft_strjoin(cmd->cmd, ": command not found"), 1) + 128);
		if (execve(path, cmd->args, g_data.env))
			exit(ft_perror(ft_strjoin("minishell: ", path), NULL, 0) + 127);
	}
}

int	ft_fork(t_cmd *cmd, int *pid, int last_in)
{
	int		pipes[2];

	while (cmd)
	{
		if (pipe(pipes) == -1)
			return (ft_perror("minishell", NULL, 0));
		if (!open_files(cmd))
		{
			g_data.exit_code = -1;
			*pid = fork();
			if (*pid == 0)
				forked_process(cmd, last_in, pipes);
			else if (*pid < 0)
				return (ft_perror("minishell", NULL, 0));
		}
		close(pipes[1]);
		if (last_in != 0)
			close(last_in);
		last_in = pipes[0];
		cmd = cmd->next;
	}
	close(last_in);
	return (0);
}

int	ft_execute(t_cmd *cmd)
{
	int		pid;
	int		r_status;
	int		last_in;

	g_data.loc = EXEC;
	last_in = 0;
	if (is_builtin(cmd) && !cmd->next)
	{
		run_one_builtin();
		return (0);
	}
	if (ft_fork(cmd, &pid, last_in))
		return (-1);
	if (g_data.exit_code == -1)
	{
		waitpid(pid, &r_status, 0);
		g_data.exit_code = WEXITSTATUS(r_status);
	}
	while (wait(NULL) > -1)
		;
	return (0);
}
