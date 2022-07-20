/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:19:58 by owahdani          #+#    #+#             */
/*   Updated: 2022/07/20 22:44:56 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_perror(char *name, char *error)
{
	printf("%s: ", name);
	if (!error)
	{
		perror(NULL);
		return (-1);
	}
	printf("%s\n", error);
	return (-1);
}

int	check_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			while (line[++i])
				if (line[i] == '"')
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
