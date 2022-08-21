/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:14:50 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/21 17:47:55 by owahdani         ###   ########.fr       */
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

char	*expand_line(char **line, int is_expand)
{
	char	*new;
	int		i;
	int		len;

	new = *line;
	*line = ft_strjoin(new, "\n");
	free(new);
	if (!is_expand || !ft_strchr(*line, '$'))
		return (*line);
	len = ft_strlen(*line);
	i = 0;
	while ((*line)[i])
		if ((*line)[i++] == '$')
			len += get_expansion_len(*line, &i);
	new = ft_malloc(len + 1, 1, 0);
	if (!new)
		return (NULL);
	heredoc_expand(*line, new);
	return (new);
}

int	write_2_fd(int fd, char *delimiter, int is_expand)
{
	char	*line;
	int		std_in;

	g_data.loc = HDOC;
	std_in = dup(0);
	line = ft_readline("> ");
	while (line)
	{
		if (!ft_strcmp(delimiter, line))
			return (ft_free(line, 0));
		line = expand_line(&line, is_expand);
		if (write(fd, line, ft_strlen(line)) < 0)
			return (ft_free(line, -1));
		free(line);
		line = ft_readline("> ");
	}
	dup2(std_in, 0);
	close(std_in);
	if (g_data.sig_caught)
		return (-2);
	return (0);
}

int	write_heredoc_2_file(t_cmd *cmd)
{
	t_name	*heredoc_lst;
	int		is_expand;

	unlink(cmd->heredoc_path);
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
		is_expand = write_2_fd(cmd->heredoc, heredoc_lst->name, is_expand);
		if (is_expand)
			return (is_expand);
		heredoc_lst = heredoc_lst->next;
	}
	close(cmd->heredoc);
	cmd->heredoc = open(cmd->heredoc_path, O_RDONLY, 0644);
	return ((cmd->heredoc == -1) * -1);
}

int	read_heredocs(void)
{
	t_cmd		*tmp;
	static int	i[2];
	char		*index;

	tmp = g_data.cmds;
	while (tmp)
	{
		if (tmp->heredoc_lst)
		{
			index = ft_itoa(i[0]++);
			if (!index)
				return (ft_perror("minishell", NULL, 0));
			tmp->heredoc_path = ft_strjoin("/tmp/heredoc_", index);
			if (!tmp->heredoc_path)
				return (ft_perror("minishell", NULL, 0));
			free(index);
			i[1] = write_heredoc_2_file(tmp);
			if (i[1] == -1)
				return (ft_perror("minishell", NULL, 0));
			else if (i[1] == -2)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}
