/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:23:19 by owahdani          #+#    #+#             */
/*   Updated: 2022/07/24 17:14:12 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strndup(const char *s1, size_t size)
{
	char	*str;
	size_t	len;
	size_t	i;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	if (size > len)
		size = len;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < size)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

void	*check_malloc()
{
}

void	mv_2_nxt_quote(char *line, int *i)
{
	if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
		(*i)++;
	}
	else
	{
		(*i)++;
		while (line[*i] && line[*i] != '\"')
			(*i)++;
		(*i)++;
	}
}
