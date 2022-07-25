/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 20:24:47 by owahdani          #+#    #+#             */
/*   Updated: 2022/07/25 18:39:46 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*last_token(t_token *tokens)
{
	while (tokens && tokens->next)
		tokens = tokens->next;
	return (tokens);
}

int	add_token(t_token **tokens, t_token *new, t_token *last)
{
	char	c;

	c = *(new->value);
	if (!c || c == '<' || c == '>' || c == '|')
	{
		if (c)
			join_error_str(UNXPCT, new->value);
		else
			join_error_str(UNXPCT, "newline");
		return (-1);
		free(new);
	}
	if (new->type == PIPE && (!*tokens || last->type == PIPE))
	{
		join_error_str(UNXPCT, "|");
		return (-1);
		free(new);
	}
	if (!*tokens)
		*tokens = new;
	else
		last->next = new;
	return (0);
}

t_token	*clear_token_lst(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp);
	}
	return (NULL);
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

t_token	*make_token_lst(char *line)
{
	t_token	*tokens;
	t_token	*new;

	tokens = NULL;
	new = get_token(&line);
	while (new)
	{
		if (new->type == OTHER && new->value == NULL)
		{
			free(new);
			new = last_token(tokens);
			if (!tokens || new->type != PIPE)
				break ;
			/*else if (new->type == PIPE)
				join_error_str(UNXPCT, new->value);*/
			join_error_str(UNXPCT, "newline");
			return (clear_token_lst(tokens));
		}
		if (add_token(&tokens, new, last_token(tokens)))
			return (clear_token_lst(tokens));
		free(new);
		new = get_token(&line);
	}
	return (tokens);
}
