/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:46:34 by owahdani          #+#    #+#             */
/*   Updated: 2022/08/06 17:07:34 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parse_line(char *line)
{
	t_token	*tokens;

	if (check_quotes(line))
		return (-1);
	tokens = make_token_lst(line);
	if (!tokens)
		return (-1);
	if (ft_expand(tokens))
		return (-1);
	clear_token_lst(tokens);
	return (0);
}
