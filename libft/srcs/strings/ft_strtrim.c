/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:17:42 by owahdani          #+#    #+#             */
/*   Updated: 2021/11/22 23:21:35 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

static int	ft_isset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_isset(*s1, set))
		s1++;
	i = ft_strlen(s1);
	if (i)
		i--;
	while (i > 0 && ft_isset(s1[i], set))
		i--;
	str = ft_substr(s1, 0, ++i);
	if (!str)
		return (NULL);
	return (str);
}
