/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owahdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:05:20 by owahdani          #+#    #+#             */
/*   Updated: 2021/11/20 02:34:54 by owahdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_allocate(int n)
{
	int		len;

	len = 0;
	if (!n || n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*arr;
	unsigned int	num;
	int				len;

	len = ft_allocate(n);
	arr = malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	arr[len--] = 0;
	if (!n)
		arr[len] = '0';
	if (n < 0)
	{
		arr[0] = '-';
		num = n * -1;
	}
	else
		num = n;
	while (num)
	{
		arr[len--] = '0' + num % 10;
		num /= 10;
	}
	return (arr);
}
