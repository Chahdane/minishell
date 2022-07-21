/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 00:19:41 by owahdani          #+#    #+#             */
/*   Updated: 2021/11/15 00:57:57 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dst_ptr;
	char	*src_ptr;

	if (!len || dst == src)
		return (dst);
	i = 0;
	dst_ptr = (char *) dst;
	src_ptr = (char *) src;
	if (dst_ptr < src_ptr)
	{
		while (i < len)
		{
			dst_ptr[i] = src_ptr[i];
			i++;
		}
	}
	else
	{
		while (len--)
			dst_ptr[len] = src_ptr[len];
	}
	return (dst);
}
