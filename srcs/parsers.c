/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:46:34 by owahdani          #+#    #+#             */
/*   Updated: 2022/07/25 17:32:17 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_tokens(t_token *tokens)
{
	char	*str;
	char	*pipe;
	char	*type;

	pipe = "|";
	while (tokens)
	{
		if (tokens->type == PIPE)
			str = pipe;
		else
			str = tokens->value;
		if (tokens->type == PIPE)
			type = "pipe";
		if (tokens->type == INF)
			type = "infile";
		if (tokens->type == OUTF)
			type = "outfile";
		if (tokens->type == APPF)
			type = "appendfile";
		if (tokens->type == HRDOC)
			type = "heredoc";
		if (tokens->type == OTHER)
			type = "other";
		printf("TOK=\"%s\", TYPE=%s\n", str, type);
		tokens = tokens->next;
	}
}

int	parse_line(char *line)
{
	t_token	*tokens;

	tokens = make_token_lst(line);
	if (!tokens)
		return (-1);
	print_tokens(tokens);
	clear_token_lst(tokens);
	return (0);
}
