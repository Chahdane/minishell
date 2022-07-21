/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:36:44 by owahdani          #+#    #+#             */
/*   Updated: 2021/11/16 19:20:02 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	chr;
	unsigned char	*str;

	if (!n)
		return (NULL);
	i = 0;
	str = (unsigned char *)s;
	chr = (unsigned char)c;
	while (i < n - 1 && str[i] != chr)
		i++;
	if (str[i] == chr)
		return (str + i);
	return (NULL);
}
