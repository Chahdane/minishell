/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:26:20 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/15 22:39:01 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_open(t_cmd *cmd, t_name *files, int flags, char *error)
{
	if (files->f_mode == NEW || files->f_mode == APP)
	{
		close(cmd->out_file);
		if (files->f_mode == APP)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		cmd->out_file = open(files->name, flags, 0644);
		if (cmd->out_file < 0)
		{
			g_data.exit_code = 1;
			return (ft_perror(error, NULL, 0));
		}
	}
	if (files->f_mode == IN)
	{
		close(cmd->in_file);
		cmd->in_file = open(files->name, O_RDONLY);
		if (cmd->in_file < 0)
		{
			g_data.exit_code = 1;
			return (ft_perror(error, NULL, 0));
		}
	}
	return (0);
}

int	open_files(t_cmd *cmd)
{
	t_name	*files;
	int		flags;
	char	*error;

	files = cmd->files;
	g_data.exit_code = 0;
	flags = O_CREAT | O_WRONLY;
	while (files)
	{
		error = ft_strjoin("minishell: ", files->name);
		if (ft_open(cmd, files, flags, error))
		{
			free(error);
			return (-1);
		}
		free(error);
		files = files->next;
	}
	return (0);
}
