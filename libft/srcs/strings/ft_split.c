/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 23:00:38 by owahdani          #+#    #+#             */
/*   Updated: 2021/11/22 23:20:04 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

static int	str_count(char const *s, char c)
{
	int	count;

	count = 1;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || !*(s + 1)))
			count++;
		s++;
	}
	return (count);
}

static	char	**ft_free(char **arr, int i)
{
	while (i > -1)
		free(arr[i--]);
	free(arr);
	return (NULL);
}

static int	char_count(char const **s, char c)
{
	int	i;

	while (**s && **s == c)
		(*s)++;
	i = 0;
	while (*(*s + i) && *(*s + i) != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	arr = malloc(sizeof(char *) * str_count(s, c));
	if (!arr)
		return (NULL);
	j = 0;
	while (*s)
	{
		i = char_count(&s, c);
		if (!i)
			break ;
		arr[j] = ft_substr(s, 0, i);
		if (!arr[j++])
			return (ft_free(arr, --j));
		s += i;
	}
	arr[j] = NULL;
	return (arr);
}
