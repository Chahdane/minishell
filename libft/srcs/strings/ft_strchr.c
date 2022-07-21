/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:51:15 by owahdani          #+#    #+#             */
/*   Updated: 2021/11/16 10:07:16 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	char	tar;

	tar = (char) c;
	while (*s && *s != tar)
		s++;
	if (*s == tar)
		return ((char *) s);
	return (NULL);
}
