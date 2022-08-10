/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:14:50 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/10 23:59:34 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*int	write_heredoc_2_files(t_cmd *cmd, int is_expand)
{
	t_name	*heredoc_lst;
	int		fd;
}*/

int	read_heredocs(void)
{
	t_cmd	*tmp;
	int		i;
	char	*index;
	int		is_expand;

	tmp = g_data.cmds;
	i = 0;
	while (tmp && tmp->heredoc_lst)
	{
		is_expand = 0;
		index = ft_itoa(i++);
		if (!index)
			return (-1);
		tmp->heredoc_path = ft_strjoin("/tmp/heredoc_", index);
		if (!tmp->heredoc_path)
			return (-1);
		free(index);
		unlink(tmp->heredoc_path);
	}
	return (0);
}
