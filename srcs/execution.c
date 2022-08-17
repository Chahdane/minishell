/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 21:30:51 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/17 01:59:08 by achahdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_streams(t_cmd *cmd, int last_in, int pipes[2])
{
	close(pipes[0]);
	if (cmd->input_source == STDIN)
	{
		dup2(last_in, 0);
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
	if (handle_streams(cmd, last_in, pipes))
		exit(g_data.exit_code);
	if (is_builtin(cmd))
	{
		exec_builtin(cmd);
		exit(g_data.exit_code);
	}
	if (ft_strchr(cmd->cmd, '/'))
	{
		if (execve(cmd->cmd, cmd->args, g_data.env))
		{
			exit(ft_perror(ft_strjoin("minishell: ", cmd->cmd), NULL, 0) + 128); // exit code = 127
		}
	}
	else
	{
		if (execve(check_path(cmd->cmd, g_data.env_lst), cmd->args, g_data.env))
			exit(ft_perror(ft_strjoin("minishell: ", cmd->cmd), NULL, 0) + 128); // exit code = 127 
		// need to change the error msg
	}
	exit(1);
}

int	ft_fork(t_cmd *cmd, int *pid)
{
	int		pipes[2];
	int		last_in;

	last_in = 0;
	while (cmd)
	{
		if (!open_files(cmd))
		{
			if (pipe(pipes) == -1)
				return (ft_perror("minishell", NULL, 0));
			*pid = fork();
			if (*pid == 0)
				forked_process(cmd, last_in, pipes);
			else if (*pid < 0)
				return (ft_perror("minishell", NULL, 0));
			close(pipes[1]);
			if (last_in != 0)
				close(last_in);
			last_in = pipes[0];
		}
		cmd = cmd->next;
	}
	close(last_in);
	return (0);
}

int	ft_execute(t_cmd *cmd)
{
	int		pid;
	int		r_status;

	if (is_builtin(cmd) && !cmd->next)
	{
		run_one_builtin();
		return (0);
	}
	ft_fork(cmd, &pid);
	waitpid(pid, &r_status, 0);
	g_data.exit_code = WEXITSTATUS(r_status);
	while (wait(NULL) > -1)
		;
	return (0);
}
