/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:46:34 by owahdani          #+#    #+#             */
/*   Updated: 2022/07/22 22:02:27 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*make_token_lst(char *line)
{
}

t_token	*get_token(char **line)
{
	t_token	*token;

	token = malloc(sizeof(token));
	while (*line)
	{
		if (*line == '|')
	}
}

int	parse_line(char *line)
{
	t_token	*tokens;

	tokens = make_token_lst(line);
	return (0);
}
