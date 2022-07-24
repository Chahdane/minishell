/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:46:34 by owahdani          #+#    #+#             */
/*   Updated: 2022/07/24 19:07:07 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*last_token(t_token *tokens)
{
	while (tokens && tokens->next)
		tokens = tokens->next;
	return (tokens);
}

int	add_token(t_token **tokens, t_token *new)
{
	if (new->type == PIPE)
	return (0);
}

t_token	*make_token_lst(char *line)
{
	t_token	*tokens;
	t_token	*tmp;

	tokens = NULL;
	tmp = get_token(&line);
	while (tmp)
	{
		if (tmp->type == OTHER && tmp->value == NULL)
		{
			free(tmp);
			if (!tokens)
				return (NULL);
			tmp = last_token(tokens);
			if (tmp->type == OTHER)
				break ;
			else if (tmp->type == PIPE)
				join_error_str(UNXPCT, tmp->value);
			else
				join_error_str(UNXPCT, "newline");
			free(tmp);
			return (clear_token_lst(tokens));
		}
		if (add_token(&tokens, tmp))
		{
			free(tmp);
			return (clear_token_lst(tokens));
		}
		free(tmp);
		tmp = get_token(&line);
	}
	return (tokens);
}

t_token	*get_token(char **line)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (check_malloc(token, NULL))
		return (NULL);
	while (**line)
	{
		if (**line == ' ')
			(*line)++;
		else if (**line == '|')
			return (get_pipe(line, token));
		else if (**line == '>')
			return (get_outfile(line, token));
		else if (**line == '<')
			return (get_input(line, token));
		else
			return (get_other(line, token));
	}
	token->value = NULL;
	token->type = OTHER;
	return (token);
}

int	parse_line(char *line)
{
	t_token	*tokens;

	tokens = make_token_lst(line);
	if (!tokens)
		return (-1);
	return (0);
}
