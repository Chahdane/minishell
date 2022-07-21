/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:14:45 by owahdani          #+#    #+#             */
/*   Updated: 2021/11/22 23:21:15 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*hay;
	char	*nee;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (i < len && haystack[i])
	{
		if (haystack[i] == *needle)
		{
			j = 0;
			hay = (char *)haystack + i;
			nee = (char *)needle;
			while (j < len - i && hay[j] && nee[j] && hay[j] == nee[j])
				j++;
			if (!needle[j])
				return (hay);
		}
		i++;
	}
	return (NULL);
}
