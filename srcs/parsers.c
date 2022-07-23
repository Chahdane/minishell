/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:46:34 by owahdani          #+#    #+#             */
/*   Updated: 2022/07/24 00:11:14 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	add_token(t_token *tokens, t_token *new)
{
}

t_token	*make_token_lst(char *line)
{
	t_token	*tokens;

	if (!token)
		;
}

t_token	*get_token(char **line)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	while (**line)
	{
		if (**line == ' ')
			(*line)++;
		else if (**line == '|')
			return (get_pipe(line, token));
		else if (**line == '>')
		{
			if (*(*line + 1) == '>')
				return (get_outfile(line, token, 1));
			else
				return (get_outfile(line, token, 0));
		}
	}
}

int	parse_line(char *line)
{
	t_token	*tokens;

	tokens = make_token_lst(line);
	return (0);
}
