/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:08:59 by owahdani          #+#    #+#             */
/*   Updated: 2021/11/16 11:46:51 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	char	tar;
	char	*str;

	tar = (char) c;
	str = (char *) s;
	while (*str)
		str++;
	while (str > s && *str != tar)
		str--;
	if (*str == tar)
		return (str);
	return (NULL);
}
