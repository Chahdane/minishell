/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:26:20 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/14 23:18:50 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_open(t_cmd *cmd, t_name *files, int flags)
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
			return (ft_perror("minishell", NULL, 0));
		}
	}
	if (files->f_mode == IN)
	{
		close(cmd->in_file);
		cmd->in_file = open(files->name, O_RDONLY);
		if (cmd->in_file < 0)
		{
			g_data.exit_code = 1;
			return (ft_perror("minishell", NULL, 0));
		}
	}
	return (0);
}

int	open_files(t_cmd *cmd)
{
	t_name	*files;
	int		flags;

	files = cmd->files;
	g_data.exit_code = 0;
	flags = O_CREAT | O_WRONLY;
	while (files)
	{
		if (ft_open(cmd, files, flags))
			return (-1);
		files = files->next;
	}
	return (0);
}
