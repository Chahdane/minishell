/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:31:20 by owahdani          #+#    #+#             */
/*   Updated: 2022/07/24 00:08:09 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*void	mv_2_nxt_quote(char **line)
{
	if (**line == '\'')
	{
		(*line)++;
		while (**line && **line != '\'')
			(*line)++;
		(*line)++;
	}
	else
	{
		(*line)++;
		while (**line && **line != '\"')
			(*line)++;
		(*line)++;
	}
}*/

t_token	*get_names(char **line, t_token *token)
{
	int	i;

	i = 0;
	while (*line[i] && *line[i] != '<' && *line[i] != '>' && *line[i] != '|')
		i++;
	if (!i)
	{
		token->value = malloc(2);
		if (!token->value)
		{
			free(token);
			return (NULL);
		}
		token->value[0] = *line[i];
		token->value[1] = 0;
		(*line)++;
		return (token);
	}
	token->value = ft_strndup(*line, i);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	(*line) += i;
}

t_token	*get_pipe(char **line, t_token *token)
{
	(*line)++;
	token->value = NULL;
	token->type = PIPE;
	token->next = NULL;
	return (token);
}

t_token	*get_outfile(char **line, t_token *token, int append)
{
	(*line)++;
	token->type = OUTF;
	if (append)
	{
		(*line)++;
		token->type = APPF;
	}
	token->next = NULL;
	while (**line == ' ')
		(*line)++;
	return (get_names(line, token));
}

int	check_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			while (line[++i])
				if (line[i] == '\"')
					break ;
		}
		else if (line[i] == '\'')
		{
			while (line[++i])
				if (line[i] == '\'')
					break ;
		}
		if (!line[i])
			return (ft_perror("minishell", QUOTES));
		i++;
	}
	return (0);
}
