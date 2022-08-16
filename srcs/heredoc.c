/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:14:50 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/16 16:38:56 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	heredoc_expand(char *line, char *new)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (line[i])
		check_n_expand(line, new, &i, &j);
	new[j] = 0;
	free(line);
}

char	*expand_line(char *line, int is_expand)
{
	char	*new;
	int		i;
	int		len;

	if (!is_expand || !ft_strchr(line, '$'))
		return (line);
	len = ft_strlen(line);
	i = 0;
	while (line[i])
		if (line[i++] == '$')
			len += get_expansion_len(line, &i);
	new = ft_malloc(len + 1, 1, 0);
	if (!new)
		return (NULL);
	heredoc_expand(line, new);
	return (new);
}

int	write_2_fd(int fd, char *delimiter, int is_expand)
{
	char	*line;
	char	*tmp;

	line = readline("> ");
	while (line)
	{
		if (!ft_strcmp(delimiter, line))
		{
			free(line);
			return (0);
		}
		tmp = line;
		line = ft_strjoin(tmp, "\n");
		free(tmp);
		line = expand_line(line, is_expand);
		if (write(fd, line, ft_strlen(line)) < 0)
		{
			free(line);
			return (-1);
		}
		free(line);
		line = readline("> ");
	}
	return (0);
}

int	write_heredoc_2_file(t_cmd *cmd)
{
	t_name	*heredoc_lst;
	int		is_expand;

	heredoc_lst = cmd->heredoc_lst;
	while (heredoc_lst)
	{
		is_expand = 1;
		if (ft_strchr(heredoc_lst->name, '\'')
			|| ft_strchr(heredoc_lst->name, '\"'))
			is_expand = 0;
		remove_quotes(heredoc_lst->name);
		close(cmd->heredoc);
		cmd->heredoc = open(cmd->heredoc_path,
				O_CREAT | O_RDWR | O_TRUNC | O_APPEND, 0644);
		if (cmd->heredoc == -1)
			return (-1);
		if (write_2_fd(cmd->heredoc, heredoc_lst->name, is_expand))
			return (-1);
		heredoc_lst = heredoc_lst->next;
	}
	close(cmd->heredoc);
	cmd->heredoc = open(cmd->heredoc_path, O_RDONLY, 0644);
	if (cmd->heredoc == -1)
		return (-1);
	return (0);
}

int	read_heredocs(void)
{
	t_cmd	*tmp;
	int		i;
	char	*index;

	tmp = g_data.cmds;
	i = 0;
	while (tmp)
	{
		if (tmp->heredoc_lst)
		{
			index = ft_itoa(i++);
			if (!index)
				return (ft_perror("minishell", NULL, 0));
			tmp->heredoc_path = ft_strjoin("/tmp/heredoc_", index);
			if (!tmp->heredoc_path)
				return (ft_perror("minishell", NULL, 0));
			free(index);
			unlink(tmp->heredoc_path);
			if (write_heredoc_2_file(tmp))
				return (ft_perror("minishell", NULL, 0));
		}
		tmp = tmp->next;
	}
	return (0);
}
