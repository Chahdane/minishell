/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizers_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:31:20 by owahdani          #+#    #+#             */
/*   Updated: 2022/07/25 23:39:16 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*get_name(char **line, t_token *token)
{
	int	i;

	while (**line == ' ')
		(*line)++;
	if (!**line || **line == '<' || **line == '>' || **line == '|')
	{
		i = 1;
		if (**line == '>' || **line == '<')
			if (**line == *(*line + 1))
				i++;
		token->value = ft_strndup(*line, i);
		if (check_malloc(token->value, token))
			return (NULL);
		(*line) += i;
		return (token);
	}
	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == ' ' || (*line)[i] == '<' || (*line)[i] == '>' || (*line)[i] == '|')
			break ;
		else if ((*line)[i] == '\'' || (*line)[i] == '\"') 
			mv_2_nxt_quote(*line, &i);
		else
			i++;
	}
	token->value = ft_strndup(*line, i);
	if (check_malloc(token->value, token))
		return (NULL);
	(*line) += i;
	return (token);
}

t_token	*get_other(char **line, t_token *token)
{
	token->type = OTHER;
	token->next = NULL;
	return (get_name(line, token));
}

t_token	*get_pipe(char **line, t_token *token)
{
	(*line)++;
	token->value = ft_strdup("?");
	if (check_malloc(token->value, token))
		return (NULL);
	token->type = PIPE;
	token->next = NULL;
	return (token);
}

t_token	*get_outfile(char **line, t_token *token)
{
	(*line)++;
	token->type = OUTF;
	if (**line == '>')
	{
		(*line)++;
		token->type = APPF;
	}
	token->next = NULL;
	return (get_name(line, token));
}

t_token	*get_input(char **line, t_token *token)
{
	(*line)++;
	token->type = INF;
	if (**line == '<')
	{
		(*line)++;
		token->type = HRDOC;
	}
	token->next = NULL;
	return (get_name(line, token));
}
