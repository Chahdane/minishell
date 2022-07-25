/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:18:47 by owahdani          #+#    #+#             */
/*   Updated: 2022/07/25 18:26:27 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **envp)
{
	char	*line;
	(void) ac, (void) av, (void) envp;

	g_data.prompt = PROMPT;
	line = readline(g_data.prompt);
	while (line)
	{
		parse_line(line);
		free(line);
		line = readline(g_data.prompt);
	}
	return (0);
}
