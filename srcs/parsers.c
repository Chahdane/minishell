/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahdan <achahdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:46:34 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/21 16:15:44 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*create_new_cmd(void)
{
	t_cmd	*new;

	new = ft_malloc(1, sizeof(t_cmd), 0);
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->files = NULL;
	new->out_file = -1;
	new->in_file = -1;
	new->heredoc_lst = NULL;
	new->heredoc_path = NULL;
	new->heredoc = -1;
	new->input_source = STDIN;
	new->args_lst = NULL;
	new->args = NULL;
	new->next = NULL;
	return (new);
}

int	clear_cmds_lst(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		clear_names_lst(cmds->files);
		clear_names_lst(cmds->heredoc_lst);
		clear_names_lst(cmds->args_lst);
		if (cmds->heredoc_path)
			unlink(cmds->heredoc_path);
		free(cmds->heredoc_path);
		free(cmds->args);
		if (cmds->heredoc > 0)
			close(cmds->heredoc);
		if (cmds->out_file > 0)
			close(cmds->out_file);
		if (cmds->in_file)
			close(cmds->in_file);
		free(cmds);
		cmds = tmp;
	}
	g_data.cmds = NULL;
	return (-1);
}

int	fill_in_cmds(t_token *token, t_cmd *new)
{
	if (token->type == INF)
	{
		new->input_source = INFILE;
		if (add_name(&new->files, token))
			return (-1);
	}
	else if (token->type == OUTF || token->type == APPF)
	{
		if (add_name(&new->files, token))
			return (-1);
	}
	else if (token->type == HRDOC)
	{
		new->input_source = HEREDOC;
		if (add_name(&new->heredoc_lst, token))
			return (-1);
	}
	else if (token->type == OTHER)
	{
		if (add_name(&new->args_lst, token))
			return (-1);
		if (!new->cmd)
			new->cmd = new->args_lst->name;
	}
	return (0);
}

int	transform_tokens(t_token *tokens)
{
	t_cmd	*new;

	g_data.cmds = create_new_cmd();
	if (!g_data.cmds)
		return (-1);
	new = g_data.cmds;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			new->next = create_new_cmd();
			if (!new->next)
				return (clear_cmds_lst(g_data.cmds));
			new = new->next;
		}
		else if (fill_in_cmds(tokens, new))
			return (clear_cmds_lst(g_data.cmds));
		tokens = tokens->next;
	}
	new = g_data.cmds;
	while (new)
		if (args_lst_to_arr(&new))
			return (clear_cmds_lst(g_data.cmds));
	return (0);
}

int	parse_line(char *line)
{
	t_token	*tokens;

	if (check_quotes(line))
		return (-1);
	tokens = make_token_lst(line);
	if (!tokens || ft_expand(tokens))
		return (clear_token_lst(tokens) == NULL);
	if (transform_tokens(tokens))
		return (clear_token_lst(tokens) == NULL);
	if (read_heredocs())
		return (clear_token_lst(tokens) == NULL);
	clear_token_lst(tokens);
	return (0);
}
