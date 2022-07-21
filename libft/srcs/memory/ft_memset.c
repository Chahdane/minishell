/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 23:43:09 by owahdani          #+#    #+#             */
/*   Updated: 2021/11/13 18:56:13 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	var;

	i = 0;
	ptr = (unsigned char *) b;
	var = (unsigned char) c;
	while (i < len)
		ptr[i++] = var;
	return (b);
}
