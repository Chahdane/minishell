/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 23:59:42 by owahdani          #+#    #+#             */
/*   Updated: 2021/11/14 23:35:09 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst_ptr;
	char	*src_ptr;

	if (!n || dst == src)
		return (dst);
	i = 0;
	dst_ptr = (char *) dst;
	src_ptr = (char *) src;
	if (dst_ptr < src_ptr)
	{
		while (i < n)
		{
			dst_ptr[i] = src_ptr[i];
			i++;
		}
	}
	else
	{
		while (n--)
			dst_ptr[n] = src_ptr[n];
	}
	return (dst);
}
