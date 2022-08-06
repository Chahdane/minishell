/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:46:34 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/06 23:55:16 by owahdani         ###   ########.fr       */
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
	new->infiles = NULL;
	new->outfiles = NULL;
	new->out_mode = NEW;
	new->heredoc_lst = NULL;
	new->heredoc = -1;
	new->input_source = STDIN;
	new->args_lst = NULL;
	new->args = NULL;
	new->next = NULL;
}

int	clear_cmds_lst(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free(cmds->cmd);
		clear_names_lst(cmds->infiles);
		clear_names_lst(cmds->outfiles);
		clear_names_lst(cmds->heredoc_lst);
		clear_names_lst(cmds->args_lst);
		free(cmds->args);
		free(cmds);
		cmds = tmp;
	}
	g_data.cmds = NULL:
	return (-1);
}

int	fill_in_cmds(t_token *token, t_cmd *new)
{
	if (token->type == INF)
	{
		new->input_source = INFILE;
	}
}

int	transfrom_tokens(t_token *tokens)
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
				return (clear_cmds_lst(cmds));
		}
		else
		tokens = tokens->next;
	}
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
	clear_token_lst(tokens);
	return (0);
}
